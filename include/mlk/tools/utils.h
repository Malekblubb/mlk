//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_TOOLS_UTILS_H
#define MLK_TOOLS_UTILS_H


#include <iostream>
#include <string>
#include <cstdlib>


namespace mlk
{
	// calls operator<< of 'os' and exits
	// with return EXIT_FAILURE
	template<typename T = std::ostream>
	void exit_with(const std::string& reason, T& os = std::cerr)
	{os << reason; std::exit(EXIT_FAILURE);}
}


#endif // MLK_TOOLS_UTILS_H
