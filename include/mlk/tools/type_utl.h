//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_TOOLS_TYPE_UTL_H
#define MLK_TOOLS_TYPE_UTL_H


#include <string>


namespace mlk
{
	namespace type_utl
	{
		// checks if given type "T" is from type string
		template<typename T>
		class is_str
		{
		public:
			static constexpr bool m_value{std::is_same<T, std::string>::value ||
						std::is_same<typename std::decay<T>::type, const char*>::value ||
						std::is_same<typename std::decay<T>::type, char*>::value};
		};

		// checks if given type "T" is from type string or int
		template<typename T>
		class is_str_or_int
		{
		public:
			static constexpr bool m_value{is_str<T>::m_value ||
						std::is_integral<T>::value};
		};
	}
}



#endif // MLK_TOOLS_TYPE_UTL_H
