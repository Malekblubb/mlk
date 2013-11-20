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


namespace mlk
{
	namespace ntw
	{
		class ip_address
		{
			std::string m_port{"0"};
			std::string m_resolved_ip{"0.0.0.0"};

		public:
			ip_address() = default;

			ip_address(const std::string& address, bool resolve = true)
			{
				std::pair<std::string, std::string> p{internal::split_address(address)};
				resolve ? m_resolved_ip = internal::ip_from_host(p.first) : m_resolved_ip = p.first;
				m_port = p.second;
			}

			template<typename T>
			ip_address(const std::string& address, const T& port, bool resolve = true) :
				ip_address{internal::merge_address(std::make_pair(address,
																  stl_string::is_numeric(stl_string::to_string(port)) ? stl_string::to_string(port) : "0")), resolve}
			{static_assert(type_utl::is_str_or_int<T>(), "string or integral type required");}


			const std::string& ip() const noexcept {return m_resolved_ip;}

			template<typename T = int>
			T port() const noexcept
			{
				static_assert(std::is_integral<T>(), "integral type required");
				return stl_string::to_int<T>(m_port);
			}

			friend std::ostream& operator<<(std::ostream&, const ip_address&);
			friend bool operator==(const ip_address&, const ip_address&);
		};

		template<>
		inline std::string ip_address::port<std::string>() const noexcept
		{return m_port;}

		inline std::ostream& operator<<(std::ostream& os, const ip_address& address)
		{
			os << address.m_resolved_ip << ":" << address.m_port;
			return os;
		}

		inline bool operator==(const ip_address& lhs, const ip_address& rhs)
		{return ((lhs.m_resolved_ip == rhs.m_resolved_ip) && (lhs.m_port == rhs.m_port));}
	}
}


#endif // MLK_NETWORK_ADDRESS_H
