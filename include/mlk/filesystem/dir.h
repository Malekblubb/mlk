//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_FILESYSTEM_DIR_H
#define MLK_FILESYSTEM_DIR_H


#include <string>
#include <sys/stat.h>


namespace mlk
{
	namespace fs
	{
		namespace dir
		{
			// checks if a dir exists
			inline bool exists(const std::string& path)
			{
				struct stat s{0};
				stat(path.c_str(), &s);
				return s.st_mode & S_IFDIR;
			}

			inline bool create(const std::string& path)
			{
				return mkdir(path.c_str(), 0755);
			}
		}
	}
}


#endif // MLK_FILESYSTEM_DIR_H
