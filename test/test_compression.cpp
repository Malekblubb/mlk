#include <mlk/compression/compression.h>

#include <iostream>


int main()
{
	// data
	mlk::data_packet raw_data{'d', 'a', 't', 'a'};

	// create compressor
	mlk::cmprs::compressor<mlk::cmprs::cmprs_mode::zlib> zlib_cmprs{raw_data};
	auto size(zlib_cmprs.pack()); // store the size; needed for unpack
	std::cout << zlib_cmprs.get().data() << std::endl; // prints the packed data: x�KI,I

	zlib_cmprs.unpack(size); // uncompress
	std::cout << zlib_cmprs.get().data() << std::endl; // prints the unpacked data: data
}