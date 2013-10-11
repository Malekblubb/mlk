//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_FILESYSTEM_FILESYSTEM_H
#define MLK_FILESYSTEM_FILESYSTEM_H


#include "dir.h"
#include "file.h"

#include <mlk/log/log.h>
#include <mlk/tools/stl_string_utl.h>

#include <cstdint>


namespace mlk
{
	namespace fs
	{
		enum class fs_type : char
		{
			dir = 0,
			file
		};


		template<fs_type type>
		class fs_handle;

		template<>
		class fs_handle<fs_type::dir>
		{
			std::string m_path;

		public:
			fs_handle() = default;
			fs_handle(const std::string& path) :
				m_path(path) {}

			bool exists() const {return dir::exists(m_path);}
			bool create() const {return dir::create(m_path);}
		};

		template<>
		class fs_handle<fs_type::file>
		{
			std::string m_path;
			std::fstream m_stream;
			bool m_needOpen;


		public:
			fs_handle(const std::string& path) :
				m_path(path),
				m_needOpen(true) {}
			~fs_handle()
			{
				if(m_stream.is_open())
					m_stream.close();
			}

			bool exists() const {return file::exists(m_path);}
			bool create() const {return file::create(m_path);}
			bool open_io(const std::ios::openmode& modes)
			{
				m_stream.open(m_path, modes);
				m_needOpen = false;
				return m_stream.is_open();
			}


			template<typename T>
			uint64_t write(const T& val)
			{
				std::string str{stl_string::to_string(val)};
				return this->write_impl(str);
			}

			template<typename T>
			uint64_t write_line(const T& val)
			{
				std::string str{stl_string::to_string(val) + "\n"};
				return this->write_impl(str);
			}

			void read_all(std::string& dest)
			{
				if(m_needOpen)
				{
					lerr() << "can not read from closed stream.";
					return;
				}

				uint64_t wasPos{m_stream.tellg()};
				std::string s;
				m_stream.seekg(0);
				while(std::getline(m_stream, s))
				{
					dest += s + "\n";
				}

				m_stream.seekg(wasPos);
			}

		private:
			uint64_t write_impl(const std::string& str)
			{
				if(m_needOpen)
				{
					lerr() << "can not write into closed stream.";
					return -1;
				}
				uint64_t start{m_stream.tellp()};
				m_stream.write(str.c_str(), str.length());
				uint64_t end{m_stream.tellp()};

				return end - start;
			}
		};
	}
}


#endif // MLK_FILESYSTEM_FILESYSTEM_H
