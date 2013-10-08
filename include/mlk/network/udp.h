//
// Copyright (c) 2013 Christoph Malek
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
			sock(const ip_address& bind_address)
			{
				m_sock = internal::get_sock(SOCK_DGRAM, 0);
				internal::bind_sock(m_sock, bind_address.ip(), bind_address.port<uint16_t>());
				this->set_blocking(blocking);
			}

			ssize_t send(const ip_address& to, const std::vector<unsigned char>& data) override
			{
				sockaddr_in sock_addr = internal::to_sockaddr_in(to.ip(), to.port<uint16_t>());
				return sendto(m_sock, data.data(), data.size(), 0, reinterpret_cast<sockaddr*>(&sock_addr), sizeof sock_addr);
			}

			ssize_t recv(ip_address& from, std::vector<unsigned char>& data, size_t max_len) override
			{
				data.clear();

				sockaddr_in sock_addr{0};
				socklen_t addr_size{sizeof sock_addr};
				ssize_t got{recvfrom(m_sock, &data[0], max_len, 0, reinterpret_cast<sockaddr*>(&sock_addr), &addr_size)};

				from = ip_address{merge_address(internal::from_sockaddr_in(sock_addr))};
				return got;
			}
		};
	}
}



#endif // MLK_NETWORK_UDP_H
