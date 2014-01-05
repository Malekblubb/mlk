//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_TOOLS_COMPILETIME_H
#define MLK_TOOLS_COMPILETIME_H


namespace mlk
{
	template<typename T>
	constexpr T get_upper(T t)
	{return t + 1;}

	template<typename T>
	constexpr T get_lower(T t)
	{return t - 1;}
}


#endif // MLK_TOOLS_COMPILETIME_H
