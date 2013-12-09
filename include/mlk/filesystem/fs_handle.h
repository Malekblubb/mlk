//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_FILESYSTEM_FS_HANDLE_H
#define MLK_FILESYSTEM_FS_HANDLE_H


#include "fs_base.h"

#include "dir.h"
#include "file.h"

#include <mlk/log/log_impl.h>
#include <mlk/tools/stl_string_utl.h>

#include <cstdint>


namespace mlk
{
	namespace fs
	{
		enum class fs_type : char
		{dir = 0, file};


		template<fs_type type>
		class fs_handle;

		template<>
		class fs_handle<fs_type::dir> : public internal::fs_base
		{
		public:
			fs_handle(const std::string& path) :
				fs_base{path}
			{ }

			bool exists() const noexcept override {return dir::exists(m_path);}
			bool create() const noexcept override {return dir::create(m_path);}
		};

		template<>
		class fs_handle<fs_type::file> : public internal::fs_base
		{
			std::fstream m_stream;
			bool m_need_open{true};

		public:
			fs_handle(const std::string& path) :
				fs_base{path}
			{ }
			~fs_handle()
			{
				if(m_stream.is_open())
					m_stream.close();
			}

			bool exists() const noexcept override {return file::exists(m_path);}
			bool create() const noexcept override {return file::create(m_path);}
			bool open_io(const std::ios::openmode& modes)
			{
				m_stream.close();
				m_stream.open(m_path, modes);
				m_need_open = false;
				return m_stream.is_open();
			}


			template<typename T>
			int64_t write(const T& val)
			{
				std::string str{stl_string::to_string(val)};
				return this->write_impl(str);
			}

			template<typename T>
			int64_t write_line(const T& val)
			{
				std::string str{stl_string::to_string(val) + "\n"};
				return this->write_impl(str);
			}

			std::size_t read_all(std::string& dest)
			{
				this->check_open();

				int64_t was_pos{m_stream.tellg()};
				std::string s;
				std::size_t count{0};
				m_stream.seekg(0);
				while(std::getline(m_stream, s))
				{
					dest += s + "\n";
					++count;
				}
				m_stream.seekg(was_pos);
				return count;
			}

			bool read_line(std::string& line) noexcept
			{
				this->check_open();
				return std::getline(m_stream, line) != nullptr;
			}

		private:
			int64_t write_impl(const std::string& str)
			{
				if(m_need_open)
				{
					lout("mlk::fs") << "can not write into closed stream. opening in mode 'std::ios::out | std::ios::app'";
					this->open_io(std::ios::out | std::ios::app);
				}
				int64_t start{m_stream.tellp()};
				m_stream.write(str.c_str(), str.length());
				int64_t end{m_stream.tellp()};

				return end - start;
			}

			void check_open() noexcept
			{
				if(m_need_open)
				{
					lout("mlk::fs") << "can not read from closed stream. opening in mode 'std::ios::in'";
					this->open_io(std::ios::in);
				}
			}
		};
	}
}


#endif // MLK_FILESYSTEM_FS_HANDLE_H
