//
// Copyright (c) 2013-2017 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_TOOLS_STL_STRING_UTL_H
#define MLK_TOOLS_STL_STRING_UTL_H

#include <mlk/tools/type_utl.h>
#include <mlk/types/types.h>

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <sstream>
#include <string>
#include <type_traits>

namespace mlk
{
	namespace stl_string
	{
		template <typename T>
		std::string to_string(const T& val)
        {
			std::ostringstream stre;
			stre << val;
			return stre.str();
		}

		template <>
		inline std::string to_string<std::string>(const std::string& str)
		{
			return str;
		}

		template <typename T = int>
		T to_int(const std::string& val)
		{
			static_assert(std::is_integral<T>(),
						  "only integral types supported");

			std::istringstream stre{val};
			T ret;
			stre >> ret;
			return ret;
		}

		template <typename T = int>
		T to_hex_int(const std::string& val)
		{
			static_assert(std::is_integral<T>(),
						  "only integral types supported");

			std::istringstream stre{val};
			T ret;
			stre >> std::hex >> ret;
			return ret;
		}

		inline data_packet to_data_packet(const std::string& str)
		{
			return {std::begin(str), std::end(str)};
		}

		// checks whether given string 'str'
		// contains only digits
		inline bool is_numeric(const std::string& str)
		{
			return !str.empty() &&
				   (std::find_if(str.begin(), str.end(), [](char find) {
						return !std::isdigit(find);
					}) == str.end());
		}

		inline bool contains_number(const std::string& str)
		{
			return !str.empty() &&
				   (std::find_if(str.begin(), str.end(), [](char find) {
						return std::isdigit(find);
					}) != str.end());
		}

		inline long count_of(char find, const std::string& str)
		{
			return std::count(str.begin(), str.end(), find);
		}

		inline std::size_t count_of(const std::string& find,
									const std::string& str)
		{
			std::size_t count{0};
			auto pos(str.find(find));
			while(pos != std::string::npos) {
				pos = str.find(find, pos + find.size());
				++count;
			}
			return count;
		}

		// erases all characters matching with 'erase' in 'str'
		// and returns the count of the erased characters
		inline int erase_all(char erase, std::string& str)
		{
			auto count{0};
			std::remove_if(std::begin(str), std::end(str),
						   [&erase, &count](char c) {
							   if(c == erase) ++count;
							   return c == erase;
						   });
			return count;
		}

		// sets all characters in 'str' to 'set'
		inline void set_all(char set, std::string& str)
		{
			std::transform(std::begin(str), std::end(str), std::begin(str),
						   [set](char) { return set; });
		}

		inline void replace_all(char replace, char with, std::string& str)
		{
			std::replace(std::begin(str), std::end(str), replace, with);
		}

		inline int erase_all(const std::string& erase, std::string& str)
		{
			int num_erased{0};
			auto erase_size{erase.size()};
			for(std::size_t pos{0};
				(pos = str.find(erase)) != std::string::npos;)
			{
				str.erase(str.begin() + long(pos),
						  str.begin() + long(pos + erase_size));
				++num_erased;
			}
			return num_erased;
		}

		// erases first found character 'erase' in 'str'
		inline void erase_first(char erase, std::string& str)
		{
			auto a(str.find_first_of(erase));
			if(a != std::string::npos) str.erase(a, 1);
		}

		// erases last found character 'erase' in 'str'
		inline void erase_last(char erase, std::string& str)
		{
			auto a(str.find_last_of(erase));
			if(a != std::string::npos) str.erase(a, 1);
		}

		// return true if 'str' contains 'char_str'
		// false otherwise
		template <typename T>
		bool contains(const T& char_str, const std::string& str)
		{
			return str.find(char_str) != std::string::npos;
		}

		// formats an input string
		// e.g.: str_format("The value is: %", 10);
		// will be formated to: "The value is 10"
		template <typename T>
		std::string str_format(const T& tail)
		{
			return tail;
		}

		template <typename T, typename... E>
		std::string str_format(const std::string& str, const T& head,
							   E&&... tail)
		{
			std::string result{str};
			auto pos(result.find("%%"));
			if(pos < result.size() + 2)
				result = str_format(result.replace(pos, 2, to_string(head)),
									std::forward<E>(tail)...);
			return result;
        }
	}
}

// using the '+'-operator on any arithmetic type
template <typename IntType>
typename std::enable_if<std::is_arithmetic<IntType>::value, std::string>::type
operator+(const std::string& s, IntType t)
{
	return s + mlk::stl_string::to_string(t);
}

#endif// MLK_TOOLS_STL_STRING_UTL_H
