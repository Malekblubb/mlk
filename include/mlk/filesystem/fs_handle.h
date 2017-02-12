//
// Copyright (c) 2013-2017 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_FILESYSTEM_FS_HANDLE_H
#define MLK_FILESYSTEM_FS_HANDLE_H

#include "dir_item.h"
#include "fs_base.h"

#include "dir.h"
#include "file.h"

#include <mlk/log/log_impl.h>
#include <mlk/tools/stl_string_utl.h>

#include <cstdint>
#include <vector>

namespace mlk
{
	namespace fs
	{
		enum class fs_type : char
		{
			dir = 0,
			file
		};

		using dir_contents = std::vector<dir_item>;

		template <fs_type type>
		class fs_handle;

		template <>
		class fs_handle<fs_type::dir> : public internal::fs_base
		{
		public:
			fs_handle(const std::string& path) : fs_base{path} { this->init(); }

			bool exists() const noexcept override
			{
				return dir::exists(m_path);
			}

			bool create() const noexcept override
			{
				return dir::create(m_path);
			}

			bool remove() const override { return dir::remove(m_path); }

			const std::string& get_path() const noexcept { return m_path; }

			template <bool recursive>
			dir_contents get_content()
			{
				if(!this->exists()) return {};
				dir_contents result;
				this->get_content_impl<recursive>(m_path, result);
				return result;
			}

		private:
			void init() { this->validate_path(m_path); }

			void validate_path(std::string& path)
			{
				if(path.size() < 1) return;
				if(*(path.end() - 1) != '/') path += '/';
			}

			template <bool recursive>
			void get_content_impl(const std::string& path, dir_contents& result)
			{
				auto d(opendir(path.c_str()));
				dirent* dir_entry;
				while((dir_entry = readdir(d))) {
					auto name(std::string{dir_entry->d_name});
					auto full(path + name);
					if(name == ".." || name == ".") continue;

					auto is_dir(dir::exists(full));
					if(is_dir) this->validate_path(full);
					result.push_back({name, full, is_dir ? item_type::dir
														 : item_type::file});
					if(is_dir && recursive)
						this->get_content_impl<recursive>(full, result);
				}
				closedir(d);
			}
		};

		template <>
		class fs_handle<fs_type::file> : public internal::fs_base
		{
			std::fstream m_stream;
			bool m_need_open{true};

		public:
			fs_handle() : fs_base{""} {}

			fs_handle(const std::string& path) : fs_base{path} {}

			~fs_handle()
			{
				if(m_stream.is_open()) m_stream.close();
			}

			void close() noexcept
			{
				m_stream.close();
				m_need_open = true;
			}

			bool exists() const noexcept override
			{
				return file::exists(m_path);
			}

			bool create() const noexcept override
			{
				return file::create(m_path);
			}

			bool remove() const override { return file::remove(m_path); }

			bool open_io(std::ios::openmode modes)
			{
				m_stream.close();
				m_stream.open(m_path, modes);
				m_need_open = false;
				return m_stream.is_open();
			}

			bool reopen(std::ios::openmode modes)
			{
				return this->open_io(modes);
			}

			bool reopen(const std::string& path, std::ios::openmode modes)
			{
				m_path = path;
				return this->reopen(modes);
			}

			void set_pos_begin() noexcept { m_stream.seekg(0); }

			void write(const mlk::data_packet& data)
			{
				this->check_open();
				if(!this->is_valid()) return;
				m_stream.write(reinterpret_cast<const char*>(data.data()),
							   data.size());
			}

			template <typename T>
			int64_t write(const T& val)
			{
				std::string str{stl_string::to_string(val)};
				return this->write_impl(str);
			}

			template <typename T>
			int64_t write_line(const T& val)
			{
				std::string str{stl_string::to_string(val) + "\n"};
				return this->write_impl(str);
			}

			std::size_t read_all(std::string& dest)
			{
				this->check_open();
				if(!this->is_valid()) return 0;

				int64_t was_pos{m_stream.tellg()};
				std::string s;
				std::size_t count{0};
				m_stream.seekg(0);
				while(std::getline(m_stream, s)) {
					dest += s + "\n";
					++count;
				}
				m_stream.seekg(was_pos);
				return count;
			}

			data_packet read_all()
			{
				this->check_open();
				if(!this->is_valid()) return {};

				int64_t was_pos{m_stream.tellg()};
				auto size(this->file_size());
				this->set_pos_begin();
				data_packet result(size);
				m_stream.read(reinterpret_cast<char*>(result.data()), size);
				m_stream.seekg(was_pos);
				return result;
			}

			auto read_line(std::string& line) noexcept
				-> decltype(std::getline(m_stream, line))
			{
				this->check_open();
				return std::getline(m_stream, line);
			}

			std::size_t file_size()
			{
				auto pos(m_stream.tellg());
				m_stream.seekg(0, std::ios::end);
				auto size(m_stream.tellg());
				m_stream.seekg(pos);
				return size;
			}

		private:
			bool is_valid() const noexcept { return m_stream.is_open(); }

			int64_t write_impl(const std::string& str)
			{
				if(m_need_open) {
					lout("mlk::fs::fs_handle<fs_type::file>")
						<< "can not write into closed stream. opening in mode "
						   "'std::ios::out | std::ios::app'";
					this->open_io(std::ios::out | std::ios::app);
				}
				int64_t start{m_stream.tellp()};
				m_stream.write(str.c_str(), str.length());
				int64_t end{m_stream.tellp()};

				return end - start;
			}

			void check_open() noexcept
			{
				if(m_need_open) {
					lout("mlk::fs::fs_handle<fs_type::file>")
						<< "can not read from closed stream. opening in mode "
						   "'std::ios::in'";
					this->open_io(std::ios::in);
				}
			}
		};

		using dir_handle = fs_handle<fs_type::dir>;
		using file_handle = fs_handle<fs_type::file>;
	}
}

#endif// MLK_FILESYSTEM_FS_HANDLE_H
