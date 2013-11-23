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
			none = -1,
			black = 0,
			red,
			green,
			yellow,
			blue,
			magenta,
			cyan,
			white
		};

		inline void reset_color()
		{std::cout << "\033[0m";}

		inline void set_color(const console_color& color)
		{
			if(color == console_color::none)
			{
				reset_color();
				return;
			}
			std::cout << "\033[1;3" << enum_utl::to_int(color) << "m";
		}
	}
}


#endif // MLK_CONSOLE_CONSOLE_H
