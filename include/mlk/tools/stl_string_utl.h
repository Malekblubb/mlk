//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_TOOLS_STL_STRING_UTL_H
#define MLK_TOOLS_STL_STRING_UTL_H


#include <mlk/tools/type_utl.h>

#include <algorithm>
#include <cctype>
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

			std::istringstream stre{val};
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

		// checks whether given string 'str'
		// contains only digits
		inline bool is_numeric(const std::string& str)
		{
			return !str.empty() &&
					(std::find_if(str.begin(), str.end(), [](char find){return !std::isdigit(find);}) == str.end());
		}

		inline bool contains_number(const std::string& str)
		{
			return !str.empty() &&
					(std::find_if(str.begin(), str.end(), [](char find){return std::isdigit(find);}) != str.end());
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

		inline int erase_all(const std::string& erase, std::string& str)
		{
			int num_erased{0};
			auto pos(str.find(erase));
			while(pos != std::string::npos)
			{
				str.erase(str.begin() + pos, str.begin() + (pos + erase.size()));
				pos = str.find(erase);
				++num_erased;
			}
		}

		// erases first found character 'erase' in 'str'
		inline void erase_first(char erase, std::string& str)
		{
			auto a(str.find_first_of(erase));
			if(a != std::string::npos)
				str.erase(a, 1);
		}

		// erases last found character 'erase' in 'str'
		inline void erase_last(char erase, std::string& str)
		{
			auto a(str.find_last_of(erase));
			if(a != std::string::npos)
				str.erase(a, 1);
		}

		// return true if 'str' contains 'char_str'
		// false otherwise
		template<typename T>
		bool contains(const T& char_str, const std::string& str)
		{return str.find(char_str) != std::string::npos;}
	}
}


#endif // MLK_TOOLS_STL_STRING_UTL_H
