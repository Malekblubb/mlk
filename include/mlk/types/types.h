//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_TYPES_TYPES_H
#define MLK_TYPES_TYPES_H


#include <chrono>
#include <vector>


namespace mlk
{
	// ints
	using llong = long long;
	using ullong = unsigned long long;
	using ulong = unsigned long;
	using ushort = unsigned short;
	using uchar = unsigned char;

	// containers
	using data_packet = std::vector<uchar>;

	// time
	using hrs_time_pnt = std::chrono::time_point<std::chrono::high_resolution_clock>;
	using sys_time_pnt = std::chrono::time_point<std::chrono::system_clock>;
	using seconds = std::chrono::seconds;
	using milli_s = std::chrono::milliseconds;
	using micro_s = std::chrono::microseconds;
	using nano_s = std::chrono::nanoseconds;
}


#endif // MLK_TYPES_TYPES_H
