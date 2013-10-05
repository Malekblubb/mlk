//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_TOOLS_STL_STRING_UTL_H
#define MLK_TOOLS_STL_STRING_UTL_H


#include <string>
#include <sstream>


namespace mlk
{
	namespace stl_string
	{
		template<typename T>
		std::string to_string(const T &val)
		{
			std::ostringstream stre;
			stre << val;
			return stre.str();
		}
	}
}



#endif // MLK_TOOLS_STL_STRING_UTL_H
