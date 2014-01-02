//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_NETWORK_UDP_H
#define MLK_NETWORK_UDP_H


#include "network_utl.h"
#include "packet.h"
#include "socket.h"


namespace mlk
{
	namespace ntw
	{
		template<bool blocking>
		class sock<sock_type::udp, blocking> : public internal::sock_base
		{
		public:
			sock(const ip_address& bind_address = ip_address{"0.0.0.0", 0}) :
				internal::sock_base{internal::get_sock(SOCK_DGRAM, 0)}
			{
				internal::bind_sock(m_sock, bind_address.ip(), bind_address.port<uint16_t>());
				this->set_blocking(blocking);
			}

			ssize_t send(const ip_address& to, const data_packet& data)
			{
				this->reset_error();
				sockaddr_in sock_addr = internal::to_sockaddr_in(to.ip(), to.port<uint16_t>());
				return sendto(m_sock, data.data(), data.size(), 0, reinterpret_cast<sockaddr*>(&sock_addr), sizeof sock_addr);
			}

			ssize_t recv(ip_address& from, data_packet& data, size_t max_len)
			{
				data.clear();
				from.reset();
				this->reset_error();

				data_packet tmp(max_len);
				sockaddr_in sock_addr{};
				socklen_t addr_size{sizeof sock_addr};
				ssize_t got{recvfrom(m_sock, tmp.data(), max_len, 0, reinterpret_cast<sockaddr*>(&sock_addr), &addr_size)};
				m_error = (got < 0);

				if(!this->error())
				{
					data.insert(data.begin(), tmp.begin(), tmp.begin() + got);
					from = ip_address{internal::merge_address(internal::from_sockaddr_in(sock_addr))};
				}
				return got;
			}
		};
	}
}


#endif // MLK_NETWORK_UDP_H
