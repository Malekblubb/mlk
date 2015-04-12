//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_FILESYSTEM_DIR_H
#define MLK_FILESYSTEM_DIR_H


#include <mlk/system/detect.h>

#include <string>
#include <dirent.h>
#include <sys/stat.h>
#ifdef MLK_LINUX
#include <unistd.h>
#elif defined MLK_WIN
#include <direct.h>
#endif


namespace mlk
{
	namespace fs
	{
		namespace dir
		{
			// checks if a dir exists
			inline bool exists(const std::string& path)
			{
                struct stat s{};
				stat(path.c_str(), &s);
				return s.st_mode & S_IFDIR;
			}

			inline bool create(const std::string& path)
            {
#ifdef MLK_LINUX || defined MLK_OS_MAC
				return mkdir(path.c_str(), 0755) != -1;
#elif defined MLK_WIN
				return mkdir(path.c_str()) != -1;
#endif
                return false;
            }
			
			inline bool remove(const std::string& path)
			{
#ifdef MLK_LINUX || defined MLK_OS_MAC
				return rmdir(path.c_str()) != -1;
#elif defined MLK_WIN
				return _rmdir(path.c_str()) != -1;
#endif
                return false;
			}
		}
	}
}


#endif // MLK_FILESYSTEM_DIR_H
