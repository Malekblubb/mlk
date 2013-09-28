/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef MLK_TOOLS_STL_STRING_UTL__H
#define MLK_TOOLS_STL_STRING_UTL__H


#include <string>
#include <sstream>


namespace mlk
{
	namespace stl_string
	{
		template<typename T> std::string toString(const T &val)
		{
			std::ostringstream stre;
			stre << val;
			return stre.str();
		}
	}
}



#endif // MLK_TOOLS_STL_STRING_UTL__H
