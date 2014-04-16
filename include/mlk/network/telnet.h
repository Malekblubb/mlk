//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_NETWORK_TELNET_H
#define MLK_NETWORK_TELNET_H


#include "tcp.h"


namespace mlk
{
	namespace ntw
	{
		template<bool blocking>
		class telnet_client
		{
			sock<sock_type::tcp, blocking> m_socket;

		public:
			telnet_client() = default;

			telnet_client(const ip_address& addr)
			{m_socket.connect(addr);}

			bool connect(const ip_address& addr)
			{return m_socket.connect(addr);}

			void disconnect()
			{m_socket.reset_socket();}

			ssize_t send_line(const data_packet& data) const
			{
				auto cpy(data);
				cnt::append(data_packet{0x0D, 0x0A}, cpy);
				return m_socket.send(cpy);
			}

			ssize_t recv_line(data_packet& result, std::size_t max_len) const
			{return m_socket.recv(result, max_len);}

			const ip_address& address() const noexcept
			{return m_socket.address();}
		};
	}
}


#endif // MLK_NETWORK_TELNET_H
