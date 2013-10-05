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
		std::string to_string(const T &val)
		{
			std::ostringstream stre;
			stre << val;
			return stre.str();
		}

		// checks if given type "T" is from type string
		template<typename T>
		class is_str_type
		{
		public:
			static constexpr bool m_value{std::is_same<T, std::string>::value ||
						std::is_same<typename std::decay<T>::type, const char*>::value ||
						std::is_same<typename std::decay<T>::type, char*>::value};
		};
	}
}



#endif // MLK_TOOLS_STL_STRING_UTL_H
