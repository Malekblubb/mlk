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
			std::string m_fallback_ip_port{"0.0.0.0:0"};
			bool m_valid{false};

		public:
			ip_address() = default;

			ip_address(const std::string& address, bool resolve = true)
			{
				if((stl_string::count_of(':', address) != 1) || (stl_string::count_of('.', address) < 1))
				{this->reset(); return;}

				auto p(internal::split_address(address)); // split address and port
				resolve ? m_resolved_ip = internal::ip_from_host(p.first) : m_resolved_ip = p.first;
				m_port = p.second;

				if(!m_resolved_ip.size() || !m_port.size() || !stl_string::is_numeric(m_port)) this->invalidate(p.first);
				else m_valid = true;
			}

			template<typename T>
			ip_address(const std::string& address, const T& port, bool resolve = true) :
				ip_address{internal::merge_address(
							   std::make_pair(address, stl_string::is_numeric(stl_string::to_string(port)) ? stl_string::to_string(port) : "0")),
						   resolve}
			{static_assert(type_utl::is_str_or_int<T>(), "string or integral type required");}


			const std::string& ip() const noexcept {return m_resolved_ip;}

			template<typename T = int>
			T port() const noexcept
			{
				static_assert(std::is_integral<T>(), "integral type required");
				return stl_string::to_int<T>(m_port);
			}

			std::string to_string() const noexcept
			{
				if(!this->is_valid())
					return m_fallback_ip_port;
				return m_resolved_ip + ":" + m_port;
			}

			bool is_valid() const noexcept
			{return m_valid;}

			void reset() noexcept
			{
				m_port = "0";
				m_resolved_ip = "0.0.0.0";
				m_valid = false;
			}

			friend std::ostream& operator<<(std::ostream&, const ip_address&);
			friend bool operator==(const ip_address&, const ip_address&);
			friend bool operator!=(const ip_address&, const ip_address&);

		private:
			void invalidate(const std::string& inv_address) noexcept
			{
				m_fallback_ip_port = inv_address + ":" + m_port;
				this->reset();
			}
		};

		template<>
		inline std::string ip_address::port<std::string>() const noexcept
		{return m_port;}

		inline std::ostream& operator<<(std::ostream& os, const ip_address& address)
		{
			if(address.is_valid())
				os << address.m_resolved_ip << ":" << address.m_port;
			else
				os << address.m_fallback_ip_port;
			return os;
		}

		inline bool operator==(const ip_address& lhs, const ip_address& rhs)
		{return ((lhs.m_resolved_ip == rhs.m_resolved_ip) && (lhs.m_port == rhs.m_port));}

		inline bool operator!=(const ip_address& lhs, const ip_address& rhs)
		{return !operator ==(lhs, rhs);}
	}
}


#endif // MLK_NETWORK_ADDRESS_H
