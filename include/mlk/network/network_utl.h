//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_NETWORK_NETWORK_UTL_H
#define MLK_NETWORK_NETWORK_UTL_H


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
			inline int getSock(int type, int proto)
			{
				return socket(AF_INET, type, proto);
			}

			inline void closeSock(int sock)
			{
				close(sock);
			}

			inline int bindSock(int sock)
			{
				sockaddr_in tmpAddr{0};
				tmpAddr.sin_family = AF_INET;
				tmpAddr.sin_port = htons(0);
				tmpAddr.sin_addr.s_addr = inet_addr("0.0.0.0");

				return bind(sock, (sockaddr *)&tmpAddr, sizeof tmpAddr);
			}

			inline void setBlocking(int sock)
			{
				int op{~O_NONBLOCK};
				fcntl(sock, F_SETFL, op);
			}

			inline void setNoBlocking(int sock)
			{
				fcntl(sock, F_SETFL, O_NONBLOCK);
			}
		}
	}
}


#endif // MLK_NETWORK_NETWORK_UTL_H
