//
// Copyright (c) 2013-2017 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_FILESYSTEM_FILE_H
#define MLK_FILESYSTEM_FILE_H

#include <cstdio>
#include <fstream>
#include <string>
#include <sys/stat.h>

namespace mlk
{
	namespace fs
	{
		namespace file
		{
			// checks if a file exists
			inline bool exists(const std::string& path)
			{
				struct stat s
				{
				};
				stat(path.c_str(), &s);
				return s.st_mode & S_IFREG;
			}

			// creats a file, will override an existing file
			inline bool create(const std::string& path)
			{
				std::ofstream stream{path, std::ios::trunc};
				bool b{stream.is_open()};
				stream.close();
				return b;
			}

			inline bool remove(const std::string& path)
			{
				return std::remove(path.c_str()) == 0;
			}
		}
	}
}

#endif// MLK_FILESYSTEM_FILE_H
