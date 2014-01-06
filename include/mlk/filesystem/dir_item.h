//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_FILESYSTEM_DIR_ITEM_H
#define MLK_FILESYSTEM_DIR_ITEM_H


#include <string>


namespace mlk
{
	namespace fs
	{
		enum class item_type : char
		{dir, file};

		struct dir_item
		{
			std::string name;
			item_type type;
		};
	}
}


#endif // MLK_FILESYSTEM_DIR_ITEM_H
