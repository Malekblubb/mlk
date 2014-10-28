//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//


#include <mlk/network/network.h>

#include <iostream>


int main()
{
    mlk::ntw::udp_sock<true> udp_sock_alias; // create a blocking udp socket (alias)
    mlk::ntw::tcp_sock<false> tcp_sock_alias; // create a non-blocking tcp socket (alias)


	// create a udp socket
	mlk::ntw::sock<mlk::ntw::sock_type::udp, false> udp_sock; // the boolean sets blocking mode(true) or non-blocking mode(false)
	mlk::ntw::ip_address to_addr{"my_address.com:my_port"}; // <- this will look up the ip from host 'my_address.com'
	// possible alternative: addr{"192.168.1.1, 80, false"}; <- this will NOT look up the ip address
	mlk::data_packet data{'r', 'e', 'q', 'u', 'e', 's', 't'};

	udp_sock.send(to_addr, data); // send data to host

	mlk::ntw::ip_address from_addr;
	udp_sock.recv(from_addr, data, 1024); // better: loop this recv when mode is non-blocking

	if(!udp_sock.error())
		std::cout << data.data() << std::endl; // display the got data response

	// TCP isnt implemented yet
}
