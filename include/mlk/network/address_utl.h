//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//


#ifndef MLK_NETWORK_ADDRESS_UTL_H
#define MLK_NETWORK_ADDRESS_UTL_H


#include <mlk/tools/stl_string_utl.h>
#include "network_utl.h"

#include <utility>
#include <sstream>
#include <string>
#include <type_traits>


namespace mlk
{
	namespace ntw
	{
		inline auto split_address(const std::string& addrStr)
		-> std::pair<std::string, std::string>
		{
			if(addrStr.find(':') == std::string::npos)
				return std::make_pair("", "");

			uint64_t colonPos{addrStr.find(':')};
			return std::make_pair(addrStr.substr(0, colonPos),
								  addrStr.substr(colonPos + 1, addrStr.length() - colonPos - 1));
		}

		template<typename T>
		inline std::string merge_address(const std::string& ip, const T& port)
		{
			static_assert(std::is_integral<T>::value ||
						  mlk::stl_string::is_str_type<T>::m_value,
						  "string or intrgral type required");

			std::ostringstream strm;
			strm << ip << ":" << port;
			return strm.str();
		}
	}
}


#endif // MLK_NETWORK_ADDRESS_UTL_H
