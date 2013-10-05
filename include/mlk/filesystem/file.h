//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_FILESYSTEM_FILE_H
#define MLK_FILESYSTEM_FILE_H


#include <fstream>
#include <string>


namespace mlk
{
	namespace fs
	{
		namespace file
		{
			// checks if a file exists
			inline bool exists(const std::string& path)
			{
				struct stat s{0};
				stat(path.c_str(), &s);
				return s.st_mode & S_IFREG;
			}

			// creats a file, will override an existing file
			inline bool create(const std::string& path)
			{
				std::ifstream stream{path, std::ios::trunc};
				bool b{stream.is_open()};
				stream.close();
				return b;
			}
		}
	}
}


#endif // MLK_FILESYSTEM_FILE_H
