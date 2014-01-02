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
		class sock<sock_type::tcp, blocking>;

//		template<bool blocking>
//		class sock<sock_type::tcp, blocking> : public internal::sock_base
//		{
//			ip_address m_address;

//		public:
//			sock() :
//				internal::sock_base(internal::get_sock(SOCK_STREAM, 0))
//			{this->set_blocking(blocking);}

//			bool connect(const ip_address& to)
//			{

//			}

//			ssize_t send(const data_packet& data)
//			{}

//			ssize_t recv(data_packet &data, size_t max_len)
//			{}
//		};
	}
}


#endif // MLK_NETWORK_TCP_H
