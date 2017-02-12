//
// Copyright (c) 2013-2017 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_TOOLS_MATH_H
#define MLK_TOOLS_MATH_H

#include <cmath>

namespace mlk
{
	namespace math
	{
		template <typename T>
		T round_to(T value, T to)
		{
			return (std::round(value / to)) * to;
		}
	}
}

#endif// MLK_TOOLS_MATH_H
