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


namespace mlk
{
	namespace fs
	{
		enum class fs_type : char
		{
			dir = 0,
			file
		};


		template<fs_type type> class fs_handle;

		template<> class fs_handle<fs_type::dir>
		{
			std::string m_path;


		public:
			fs_handle() = default;
			fs_handle(const std::string &path) :
				m_path(path) {}

			bool exists() const {return dir::exists(m_path);}
			bool create() const {return dir::create(m_path);}
		};

		template<> class fs_handle<fs_type::file>
		{
			std::string m_path;
			std::fstream m_stream;
			bool m_needOpen;


		public:
			fs_handle(const std::string &path) :
				m_path(path),
				m_needOpen(true) {}
			~fs_handle()
			{
				if(m_stream.is_open())
					m_stream.close();
			}

			bool exists() const {return file::exists(m_path);}
			bool create() const {return file::create(m_path);}
			bool openIo(const std::ios::openmode &modes)
			{
				m_stream.open(m_path, modes);
				m_needOpen = false;
				return m_stream.is_open();
			}


			template<typename T> long long write(const T &val)
			{
				std::string str{stl_string::toString(val)};
				return this->writeImpl(str);
			}

			template<typename T> long long writeLine(const T &val)
			{
				std::string str{stl_string::toString(val) + "\n"};
				return this->writeImpl(str);
			}

			void readAll(std::string &dest)
			{
				if(m_needOpen)
				{
					lerr("nA") << "can not read from closed stream.";
					return;
				}

				int wasPos{m_stream.tellg()};

				m_stream.seekg(0);
				std::string s;
				while(std::getline(m_stream, s))
				{
					dest += s + "\n";
				}

				m_stream.seekg(wasPos);
			}

		private:
			long long writeImpl(const std::string &str)
			{
				if(m_needOpen)
				{
					lerr("nA") << "can not write into closed stream.";
					return -1;
				}
				long long start{m_stream.tellp()};
				m_stream.write(str.c_str(), str.length());
				long long end{m_stream.tellp()};

				return end - start;
			}
		};
	}
}


#endif // MLK_FILESYSTEM_FILESYSTEM_H
