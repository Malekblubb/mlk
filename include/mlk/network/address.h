//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//


#ifndef MLK_NETWORK_ADDRESS_H
#define MLK_NETWORK_ADDRESS_H


#include "address_utl.h"
#include <mlk/tools/stl_string_utl.h>
#include <mlk/tools/type_utl.h>

#include <string>
#include <type_traits>
#include <iostream>


namespace mlk
{
	namespace ntw
	{
		class ip_address
		{
			std::string m_ip{""};
			std::string m_port{""};
			std::string m_resolvedIp{""};

		public:
			ip_address(const std::string& address)
			{
				std::pair<std::string, std::string> p{split_address(address)};
				m_ip = p.first;
				m_port = p.second;
				m_resolvedIp = internal::ip_from_host(m_ip);
			}

			ip_address(ip_address&& o) noexcept :
				m_ip(std::move(o.m_ip)),
				m_port(std::move(o.m_port)),
				m_resolvedIp(std::move(o.m_resolvedIp))
			{ }

			template<typename T>
			ip_address(const std::string& address, const T& port)
			{
				static_assert(type_utl::is_str_or_int<T>::m_value, "string or intrgral type required");

				m_ip = address;
				m_port = stl_string::to_string(port);
				m_resolvedIp = internal::ip_from_host(m_ip);
			}

			std::string ip() const noexcept {return m_resolvedIp;}
			std::string port() const noexcept {return m_port;}
		};
	}
}


#endif // MLK_NETWORK_ADDRESS_H
