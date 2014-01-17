//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_GRAPHICS_GRAPHICS_UTL_H
#define MLK_GRAPHICS_GRAPHICS_UTL_H


namespace mlk
{
	namespace gcs
	{
		// get color 'difference'
		template<typename Color_Type>
		Color_Type color_diff(const Color_Type& start_color, const Color_Type& end_color, float ration)
		{
			return {static_cast<std::uint8_t>(start_color.r + (ration * (end_color.r - start_color.r))),
					static_cast<std::uint8_t>(start_color.g + (ration * (end_color.g - start_color.g))),
					static_cast<std::uint8_t>(start_color.b + (ration * (end_color.b - start_color.b)))};
		}
	}
}


#endif // MLK_GRAPHICS_GRAPHICS_UTL_H
