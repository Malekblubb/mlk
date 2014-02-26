//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_NETWORK_TCP_H
#define MLK_NETWORK_TCP_H


#include "socket.h"


namespace mlk
{
	namespace ntw
	{
		template<bool blocking>
		class sock<sock_type::tcp, blocking> : public internal::sock_base
		{
			ip_address m_targetaddress;
			ip_address m_destaddress;

		public:
			sock(const ip_address& target = {"0.0.0.0:0"}, const ip_address& dest = {"0.0.0.0:0", false}) :
				internal::sock_base{internal::get_sock(SOCK_STREAM, 0), blocking},
				m_targetaddress{target},
				m_destaddress{dest}
			{
                internal::set_sock_opt(m_sock, SO_REUSEADDR);
				this->init();
			}

			void reset_socket() override
			{
				internal::close_sock(m_sock);
				m_sock = internal::get_sock(SOCK_STREAM, 0);
			}

			ssize_t send(const data_packet& data) const
			{
                return ::send(m_sock, reinterpret_cast<const char*>(data.data()), data.size(), 0);
			}

			ssize_t recv(data_packet& data, size_t max_len) const
			{
				return ::recv(m_sock, reinterpret_cast<char*>(data.data()), max_len, 0);
			}

			bool connect(const ip_address& target)
			{
				m_targetaddress = target;
				return this->connect();
			}

			bool connect()
			{
				this->reset_error();
				auto target_si(internal::to_sockaddr_in(m_targetaddress.ip(), m_targetaddress.port<std::uint16_t>()));
				if(::connect(m_sock, reinterpret_cast<sockaddr*>(&target_si), sizeof(sockaddr)) != 0)
				{
#ifdef MLK_LINUX
					if(errno == EISCONN) return true;
#elif defined MLK_WIN
					if(WSAGetLastError() == WSAEISCONN) return true;
#endif
					m_error = true;
					return false;
				}
				return true;
			}

			bool is_connected() const noexcept
			{return this->send({'p'}) != -1;}

		private:
			void init()
			{
				this->reset_error();
				if(m_sock < 0)
				{
					m_error = true;
					return;
				}
				auto dest_si(internal::to_sockaddr_in(m_destaddress.ip(), m_destaddress.port<std::uint16_t>()));
				if(bind(m_sock, reinterpret_cast<sockaddr*>(&dest_si), sizeof(sockaddr)) != 0)
				{
					m_error = true;
					return;
				}
			}
		};
	}
}


#endif // MLK_NETWORK_TCP_H
