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
			sock()
			{
				m_sock = internal::get_sock(SOCK_DGRAM, 0);
				this->set_blocking(blocking);
			}

			size_t send_pk(const packet& pk) override
			{

			}

			size_t recv_pk(packet& pk) override
			{

			}
		};
	}
}



#endif // MLK_NETWORK_UDP_H
