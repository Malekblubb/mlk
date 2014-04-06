//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_NETWORK_NETWORK_UTL_H
#define MLK_NETWORK_NETWORK_UTL_H


#include <mlk/system/detect.h>
#include "address.h"

#ifdef MLK_LINUX
#include <string>

extern "C"
{
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
}
#elif defined MLK_WIN
#include <winsock2.h>
#include <windows.h>
using socklen_t = mlk::uint;
#endif


namespace mlk
{
	namespace ntw
	{
		namespace internal
		{
			// low level ntw stuff
			inline void init_ntw()
			{
#ifdef MLK_WIN
				// win sux
				WSADATA data;
				WORD version{MAKEWORD(2, 2)};
				WSAStartup(version, &data);
#endif
			}

			inline void clean_ntw()
			{
#ifdef MLK_WIN
				WSACleanup();
#endif
			}

			inline int get_sock(int type, int proto)
			{
				init_ntw();
				return socket(AF_INET, type, proto);
			}

			inline void close_sock(int sock)
			{
#ifdef MLK_LINUX
				close(sock);
#elif defined MLK_WIN
				closesocket(sock);
#endif
			}

			inline sockaddr_in to_sockaddr_in(const std::string& ip, uint16_t port)
			{
#ifdef MLK_LINUX
				return sockaddr_in{AF_INET, htons(port), {inet_addr(ip.c_str())}, {0}};
#elif defined MLK_WIN
				sockaddr_in result{0, 0, {0}, {0}};
				result.sin_family = AF_INET;
				result.sin_port = htons(port);
				result.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
				return result;
#endif
			}

			inline auto from_sockaddr_in(const sockaddr_in& sock_addr)
			-> std::pair<std::string, uint16_t>
			{return std::make_pair(inet_ntoa(sock_addr.sin_addr), htons(sock_addr.sin_port));}

			inline int bind_sock(int sock, const std::string& ip, const uint16_t port)
			{
				auto tmp(to_sockaddr_in(ip, port));
				return bind(sock, reinterpret_cast<sockaddr*>(&tmp), sizeof tmp);
			}

			inline void set_blocking(int sock)
			{
#ifdef MLK_LINUX
				int op{~O_NONBLOCK};
				fcntl(sock, F_SETFL, op);
#elif defined MLK_WIN
				u_long mode{0};
				ioctlsocket(sock, FIONBIO, &mode);
#endif
			}

			inline void set_no_blocking(int sock)
			{
#ifdef MLK_LINUX
				fcntl(sock, F_SETFL, O_NONBLOCK);
#elif defined MLK_WIN
				u_long mode{1};
				ioctlsocket(sock, FIONBIO, &mode);
#endif
			}

			inline void set_sock_opt(int& sock, int opt)
			{const char* optval{"1"}; setsockopt(sock, SOL_SOCKET, opt, optval, sizeof optval);}

			inline char* get_sock_opt(const int& sock, int opt)
			{
				char* result{0};
#ifdef MLK_LINUX
				socklen_t len{sizeof result};
#elif defined MLK_WIN
				int len{sizeof result};
#endif
				getsockopt(sock, SOL_SOCKET, opt, result, &len);
				return result;
			}

			inline std::string ip_from_host(const std::string& host)
			{
				hostent* h{gethostbyname(host.c_str())};
				if(h == nullptr)
					return "";

				in_addr* a{(in_addr*)h->h_addr_list[0]};
				if(a == nullptr)
					return "";

				return inet_ntoa(*a);
			}
		}
	}
}


#endif // MLK_NETWORK_NETWORK_UTL_H
