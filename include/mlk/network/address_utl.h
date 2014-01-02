//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//


#ifndef MLK_NETWORK_ADDRESS_UTL_H
#define MLK_NETWORK_ADDRESS_UTL_H


#include <mlk/tools/type_utl.h>

#include <utility>
#include <sstream>
#include <string>


namespace mlk
{
	namespace ntw
	{
		namespace internal
		{
			inline auto split_address(const std::string& addrStr)
			-> std::pair<std::string, std::string>
			{
				uint64_t colonPos{addrStr.find(':')};
				return std::make_pair(addrStr.substr(0, colonPos),
									  addrStr.substr(colonPos + 1, addrStr.length() - colonPos - 1));
			}

			template<typename T>
			std::string merge_address(const std::pair<std::string, T>& pair)
			{
				static_assert(type_utl::is_str_or_int<T>(), "string or integral type required");

				std::ostringstream strm;
				strm << pair.first << ":" << pair.second;
				return strm.str();
			}
		}
	}
}


#endif // MLK_NETWORK_ADDRESS_UTL_H
