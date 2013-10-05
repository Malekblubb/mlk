//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//


#ifndef MLK_NETWORK_ADDRESS_H
#define MLK_NETWORK_ADDRESS_H


#include "address_utl.h"
#include <mlk/tools/stl_string_utl.h>

#include <string>
#include <type_traits>
#include <iostream>


namespace mlk
{
	namespace ntw
	{
		class ip_address
		{
		public:
			std::string m_ip;
			std::string m_port;
			std::string m_resolved_ip;
			bool m_hasPort;


		public:
			ip_address(const std::string& address)
			{
				std::pair<std::string, std::string> p{split_address(address)};
				m_ip = p.first;
				m_port = p.second;
				m_resolved_ip = internal::ip_from_host(m_ip);
			}

			ip_address(ip_address&& o) :
				m_ip(std::move(o.m_ip)),
				m_port(std::move(o.m_port)),
				m_hasPort(std::move(o.m_hasPort))
			{ }

			template<typename T>
			ip_address(const std::string& address, const T& port)
			{
				static_assert(std::is_integral<T>::value ||
							  stl_string::is_str_type<T>::m_value,
							  "string or intrgral type required");

				m_ip = address;
				m_port = stl_string::toString(port);
				m_resolved_ip = internal::ip_from_host(m_ip);
			}
		};
	}
}


#endif // MLK_NETWORK_ADDRESS_H
