//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//


#include <mlk/time/time.h>

#include <iostream>


int main()
{
	auto time_now(mlk::tm::time_stmp()); // get current time as long long; f.e.: 1385206783049705


	auto start(mlk::tm::time_pnt());

	mlk::tm::sleep(5000); // do work

	auto end(mlk::tm::time_pnt());


	std::cout << mlk::tm::duration(start, end) << std::endl; // prints 5000
	// use mlk::tm::duration<std::chrono::microseconds>(start, end) to get microseconds etc..
	std::cout << mlk::tm::timed_out(start, 1000) << std::endl; // prints 1 because the duration of start and now is higher than 1000


	std::cout << mlk::tm::time_str() << std::endl; // prints the current time as string; f.e.: Sat Nov 32 12:13:44 2013


	// timer
	mlk::tm::timer timer{1000};
	bool timed_out{false};
	mlk::slot<> timeout_slot{[&]{timed_out = true;}}; // (!) will be emited from another thread
	mlk::link_signal(timer.m_timeout, timeout_slot);

	timer.run(); // start timer
	while(!timed_out)
		/* Do something... */;
}
