//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_TOOLS_TYPE_UTL_H
#define MLK_TOOLS_TYPE_UTL_H


#include <mlk/types/types.h>

#include <string>
#include <type_traits>


namespace mlk
{
	namespace type_utl
	{
		// checks if given type "T" is from type string
		template<typename T>
		class is_str
		{
		public:
			static constexpr bool m_value{std::is_same<T, std::string>() ||
						std::is_same<typename std::decay<T>::type, const char*>() ||
						std::is_same<typename std::decay<T>::type, char*>()};
			constexpr operator bool() const {return m_value;}
			constexpr bool operator()() const {return m_value;}
		};

		// checks if given type "T" is from type string or int
		template<typename T>
		class is_str_or_int
		{
		public:
			static constexpr bool m_value{is_str<T>::m_value ||
						std::is_integral<T>()};
			constexpr operator bool() const {return m_value;}
			constexpr bool operator()() const {return m_value;}
		};

		template<typename T>
		struct is_char
		{
			static constexpr bool m_value{std::is_same<T, char>() ||
						std::is_same<T, uchar>()};
			constexpr operator bool() const {return m_value;}
			constexpr bool operator()() const {return m_value;}

		};
	}
}


#endif // MLK_TOOLS_TYPE_UTL_H
