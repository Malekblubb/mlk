//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//


#ifndef MLK_NETWORK_ADDRESS_H
#define MLK_NETWORK_ADDRESS_H


#include <mlk/tools/stl_string_utl.h>

#include <string>
#include <type_traits>


namespace mlk
{
	namespace ntw
	{
		class ip_address
		{
			std::string m_ip;
//			port_t m_port;
			bool m_hasPort;


		public:
			ip_address(const std::string& address)
			{

			}

			template<typename T>
			ip_address(const std::string& address, const T& port)
			{
				using wconst = typename std::remove_const<T>::type;

				static_assert(std::is_integral<T>::value ||
							  std::is_same<T, std::string>::value ||
							  std::is_same<T, const char*>::value,

							  "std::string or intrgral type required");

				using port_t = T;
			}




		};
	}
}


#endif // MLK_NETWORK_ADDRESS_H
