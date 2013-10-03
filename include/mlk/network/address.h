//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//


#ifndef MLK_NETWORK_ADDRESS_H
#define MLK_NETWORK_ADDRESS_H


#include <mlk/tools/stl_string_utl.h>

#include <string>


namespace mlk
{
	namespace ntw
	{
		template<typename T> class ip_address
		{
			using port_t = T;

			std::string m_ip;
			port_t m_port;
			bool m_hasPort;


		public:
			ip_address(const std::string& address)
			{

			}

			ip_address(const std::string& address, port_t port)
			{

			}
		};
	}
}


#endif // MLK_NETWORK_ADDRESS_H
