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
			sock(const ip_address& target, const ip_address& dest = {"0.0.0.0:0", false}) :
				internal::sock_base{internal::get_sock(SOCK_STREAM, 0)},
				m_targetaddress{target},
				m_destaddress{dest}
			{
				this->set_blocking(blocking);
				internal::set_sock_opt(m_sock, SO_REUSEADDR);
				this->init();
			}

			ssize_t send(const data_packet& data) const
			{return ::send(m_sock, data.data(), data.size(), 0);}

			ssize_t recv(data_packet& data, size_t max_len) const
			{return ::recv(m_sock, data.data(), max_len, 0);}

			bool connect(const ip_address& target)
			{
				m_targetaddress = target;
				return this->connect();
			}

			bool connect()
			{
				auto target_si(internal::to_sockaddr_in(m_targetaddress.ip(), m_targetaddress.port<std::uint16_t>()));
				if(::connect(m_sock, reinterpret_cast<sockaddr*>(&target_si), sizeof(sockaddr)) != 0)
				{
					m_error = true;
					return false;
				}
				return this->is_connected();
			}

			bool is_connected() const noexcept
			{return internal::get_sock_opt(m_sock, SO_ERROR) == 0;}

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
