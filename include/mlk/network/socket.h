//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_NETWORK_SOCKET_H
#define MLK_NETWORK_SOCKET_H


#include "network_utl.h"
#include "address.h"

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


		template<sock_type type, bool blocking>
		class sock;

		namespace internal
		{
			class sock_base
			{
			protected:
				int m_sock;

			public:
				~sock_base()
				{
					internal::close_sock(m_sock);
				}

				void set_blocking(bool b)
				{
					b ? internal::set_blocking(m_sock) : internal::set_no_blocking(m_sock);
				}

				virtual ssize_t send(const ip_address& to, const std::vector<unsigned char>& data) = 0;
				virtual ssize_t recv(ip_address& from, std::vector<unsigned char>& data, size_t max_len) = 0;

			private:
				int error() const noexcept
				{
					return errno;
				}
			};
		}
	}
}



#endif // MLK_NETWORK_SOCKET_H
