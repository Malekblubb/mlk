//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_TOOLS_STL_STRING_UTL_H
#define MLK_TOOLS_STL_STRING_UTL_H


#include <string>
#include <sstream>
#include <type_traits>


namespace mlk
{
	namespace stl_string
	{
		template<typename T>
		std::string to_string(const T& val)
		{
			std::ostringstream stre;
			stre << val;
			return stre.str();
		}

		template<typename T>
		T to_int(const std::string& val)
		{
			static_assert(std::is_integral<T>::value, "only integral types supported");

			std::stringstream stre{val};
			T ret;
			stre >> ret;
			return ret;
		}
	}
}



#endif // MLK_TOOLS_STL_STRING_UTL_H
