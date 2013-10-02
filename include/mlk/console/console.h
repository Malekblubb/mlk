//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_CONSOLE_CONSOLE_H
#define MLK_CONSOLE_CONSOLE_H


#include <mlk/tools/enum_utl.h>

#include <iostream>


namespace mlk
{
	namespace console
	{
		enum class console_color : char
		{
			black = 0,
			red,
			green,
			yellow,
			blue,
			magenta,
			cyan,
			white
		};

		inline void setColor(const console_color &color)
		{
			std::cout << "\033[1;3" << enum_utl::toInt(color) << "m";
		}

		inline void resetColor()
		{
			std::cout << "\033[0m";
		}
	}
}


#endif // MLK_CONSOLE_CONSOLE_H
