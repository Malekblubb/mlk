//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//


#ifndef MLK_NETWORK_ADDRESS_H
#define MLK_NETWORK_ADDRESS_H


#include "address_utl.h"
#include "network_utl.h"
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
			std::string m_port{""};
			std::string m_resolvedIp{""};

		public:
			ip_address(const ip_address&) = default;

			ip_address(const std::string& address)
			{
				std::pair<std::string, std::string> p{split_address(address)};
				m_resolvedIp = internal::ip_from_host(p.first);
				m_port = p.second;
			}

			ip_address(ip_address&& o) noexcept :
				m_port(std::move(o.m_port)),
				m_resolvedIp(std::move(o.m_resolvedIp))
			{ }

			ip_address& operator=(const ip_address&) = default;

			template<typename T>
			ip_address(const std::string& address, const T& port)
			{
				static_assert(type_utl::is_str_or_int<T>::m_value, "string or integral type required");

				m_resolvedIp = internal::ip_from_host(address);
				m_port = stl_string::to_string(port);
			}

			std::string ip() const noexcept {return m_resolvedIp;}
			std::string port() const noexcept {return m_port;}
		};
	}
}


#endif // MLK_NETWORK_ADDRESS_H
