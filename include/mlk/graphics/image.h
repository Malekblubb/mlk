//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_GRAPHICS_IMAGE_H
#define MLK_GRAPHICS_IMAGE_H


#include <mlk/log/log.h>
#include <mlk/types/types.h>

#include <pnglite.h>


namespace mlk
{
	namespace gcs
	{
		class image
		{
			mlk::data_packet m_raw_pixels;
			mlk::uint m_width, m_height;

			png_t m_pnghandle;

		public:
			image()
			{png_init(0, 0);}

			image(const mlk::data_packet& raw_pixels, mlk::uint width, mlk::uint height) :
				m_raw_pixels{raw_pixels},
				m_width{width},
				m_height{height}
			{png_init(0, 0);}

			~image()
			{png_close_file(&m_pnghandle);}


			bool save(const std::string& file)
			{
				auto error(0);
				if((error = png_open_file_write(&m_pnghandle, file.c_str())) != PNG_NO_ERROR)
				{
					mlk::lerr()["mlk::gcs::image"] << "png_open_file_write failed: " << error;
					return false;
				}

				if(m_raw_pixels.empty())
					mlk::lout("mlk::gcs::image") << "warning: pixelbuffer is empty";

				png_set_data(&m_pnghandle, m_width, m_height, 8, PNG_TRUECOLOR_ALPHA, m_raw_pixels.data());
				png_close_file(&m_pnghandle);
				return true;
			}
		};
	}
}


#endif // MLK_GRAPHICS_IMAGE_H

