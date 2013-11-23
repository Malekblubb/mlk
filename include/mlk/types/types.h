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
	using llong = long long;
	using ullong = unsigned llong;
	using ulong = unsigned long;
	using ushort = unsigned short;
	using uchar = unsigned char;
	using data_packet = std::vector<uchar>;
	using hrs_time_pnt = std::chrono::time_point<std::chrono::high_resolution_clock>;
	using sys_time_pnt = std::chrono::time_point<std::chrono::system_clock>;
}


#endif // MLK_TYPES_TYPES_H
