//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_TOOLS_STL_STRING_UTL_H
#define MLK_TOOLS_STL_STRING_UTL_H


#include <mlk/tools/type_utl.h>

#include <algorithm>
#include <cstdint>
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

		template<typename T = int>
		T to_int(const std::string& val)
		{
			static_assert(std::is_integral<T>::value, "only integral types supported");

			std::stringstream stre{val};
			T ret;
			stre >> ret;
			return ret;
		}

		template<typename T = int>
		T to_hex_int(const std::string& val)
		{
			static_assert(std::is_integral<T>::value, "only integral types supported");

			std::istringstream stre{val};
			T ret;
			stre >> std::hex >> ret;
			return ret;
		}

		inline std::size_t count_of(char find, const std::string& str)
		{return std::count(str.begin(), str.end(), find);}

		// erases all characters matching with 'erase' in 'str'
		// and returns the count of the erased characters
		inline int erase_all(char erase, std::string& str)
		{
			int num_erased{0};
			for(;;)
			{
				auto a(str.find(erase));
				if(a == std::string::npos)
					break;

				str.erase(str.begin() + a);
				++num_erased;
			}
			return num_erased;
		}

		// erases first found character 'erase' in 'str'
		inline void erase_first(char erase, std::string& str)
		{
			auto a(str.find_first_of(erase));
			if(a != std::string::npos)
				str.erase(a);
		}

		// erases last found character 'erase' in 'str'
		inline void erase_last(char erase, std::string& str)
		{
			auto a(str.find_last_of(erase));
			if(a != std::string::npos)
				str.erase(a);
		}
	}
}


#endif // MLK_TOOLS_STL_STRING_UTL_H
