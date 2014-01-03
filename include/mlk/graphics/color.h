//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_GRAPHICS_COLOR_H
#define MLK_GRAPHICS_COLOR_H


#include <mlk/tools/stl_string_utl.h>

#include <cstdint>


namespace mlk
{
	namespace gcs
	{
		class color_rgb
		{
			std::uint8_t m_r{0}, m_g{0}, m_b{0}, m_a{255};

		public:
			color_rgb() = default;

			color_rgb(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha) :
				m_r{red},
				m_g{green},
				m_b{blue},
				m_a{alpha}
			{ }

			color_rgb(const std::string& hex_str)
			{this->init_from_hex(hex_str);}

		private:
			void init_from_hex(const std::string& hex_str)
			{
				auto as_int(stl_string::to_hex_int(this->prepare_str(hex_str)));
				m_r = (as_int & 0xff0000) >> 16;
				m_g = (as_int & 0xff00) >> 8;
				m_b = (as_int & 0xff);
			}

			std::string prepare_str(const std::string& hex_str)
			{
				std::string cpy{hex_str};
				if(cpy.length() > 7)
					cpy = "#000000";
				stl_string::erase_all('#', cpy);
				return cpy;
			}

		public:
			std::uint8_t red() const noexcept {return m_r;}
			std::uint8_t green() const noexcept {return m_g;}
			std::uint8_t blue() const noexcept {return m_b;}
			std::uint8_t alpha() const noexcept {return m_a;}
		};
	}
}


#endif // MLK_GRAPHICS_COLOR_H
