//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_NETWORK_NETWORK_UTL_H
#define MLK_NETWORK_NETWORK_UTL_H


#include "address.h"

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>


namespace mlk
{
	namespace ntw
	{
		namespace internal
		{
			// low level ntw stuff
			inline int get_sock(int type, int proto)
			{
				return socket(AF_INET, type, proto);
			}

			inline void close_sock(int sock)
			{
				close(sock);
			}

			inline int bind_sock(int sock)
			{
				sockaddr_in tmpAddr{AF_INET, htons(0), inet_addr("0.0.0.0")};
				return bind(sock, (sockaddr*)&tmpAddr, sizeof tmpAddr);
			}

			inline void set_blocking(int sock)
			{
				int op{~O_NONBLOCK};
				fcntl(sock, F_SETFL, op);
			}

			inline void set_no_blocking(int sock)
			{
				fcntl(sock, F_SETFL, O_NONBLOCK);
			}

			inline std::string ip_from_host(std::string ip)
			{
				hostent* h{gethostbyname(ip.c_str())};
				if(h == nullptr)
					return "";

				in_addr* a{(in_addr*)h->h_addr_list[0]};
				if(a == nullptr)
					return "";

				return inet_ntoa(*a);
			}

			inline sockaddr_in to_sockaddr_in(const std::string& ip, uint16_t port)
			{
				return sockaddr_in{AF_INET, htons(port), inet_addr(ip.c_str())};
			}
		}
	}
}


#endif // MLK_NETWORK_NETWORK_UTL_H
