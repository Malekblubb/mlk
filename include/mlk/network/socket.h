//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_NETWORK_SOCKET_H
#define MLK_NETWORK_SOCKET_H


#include "network_utl.h"
#include "address.h"

#include <mlk/types/types.h>

#include <cerrno>
#include <vector>


namespace mlk
{
	namespace ntw
	{
		enum class sock_type : char
		{
			udp = 0,
			tcp
		};

		enum class sock_error : char
		{
			ok = 0,
			again,
			error
		};

		template<sock_type type, bool blocking>
		class sock;

		namespace internal
		{
			class sock_base
			{
			protected:
				int m_sock;
				bool m_error{true};

			public:
				sock_base(int sock) :
					m_sock{sock}
				{ }

				~sock_base()
				{internal::close_sock(m_sock);}

				void set_blocking(bool b) noexcept
				{b ? internal::set_blocking(m_sock) : internal::set_no_blocking(m_sock);}

				virtual ssize_t send(const ip_address& to, const data_packet& data) = 0;
				virtual ssize_t recv(ip_address& from, data_packet& data, size_t max_len) = 0;

				sock_error error_type() const noexcept
				{
					if(m_error)
						return sock_error::error;

					if((errno == EWOULDBLOCK) || (errno == EAGAIN))
						return sock_error::again;

					if(errno != 0)
						return sock_error::error;

					return sock_error::ok;
				}

				bool error() const noexcept
				{return error_type() != sock_error::ok;}

			protected:
				void reset_error() noexcept
				{errno = 0; m_error = false;}
			};
		}
	}
}


#endif // MLK_NETWORK_SOCKET_H
