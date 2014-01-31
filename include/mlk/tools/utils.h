//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_TOOLS_UTILS_H
#define MLK_TOOLS_UTILS_H


#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>


namespace mlk
{
	// calls operator<< of 'os' and exits
	// with return EXIT_FAILURE
	template<typename T = std::ostream>
	void exit_with(const std::string& reason, T& os = std::cerr)
	{os << reason; std::exit(EXIT_FAILURE);}

	bool parse_bool(const std::string& str)
	{
		auto cpy(str);
		mlk::stl_string::erase_all(' ', cpy);
		if(cpy.empty())
			throw std::invalid_argument{"cant parse empty string"};

		std::transform(std::begin(cpy), std::end(cpy), std::begin(cpy), [](char c){return std::tolower(c);});
		return cpy[0] == 't' || cpy[0] == '1';
	}
}


#endif // MLK_TOOLS_UTILS_H
