//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_GRAPHICS_COLOR_H
#define MLK_GRAPHICS_COLOR_H


#include <mlk/tools/stl_string_utl.h>

#include <cstdint>
#include <iomanip>


namespace mlk
{
	namespace gcs
	{
		class color_rgb
		{
			std::uint8_t m_r{0}, m_g{0}, m_b{0}, m_a{255};
			std::string m_hex;

		public:
			color_rgb() = default;

			template<typename Color_Type>
			color_rgb(const Color_Type& type) :
				color_rgb{static_cast<std::uint8_t>(type.r), static_cast<std::uint8_t>(type.g),
						  static_cast<std::uint8_t>(type.b), static_cast<std::uint8_t>(type.a)}
			{ }

			color_rgb(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = 255) :
				m_r{red},
				m_g{green},
				m_b{blue},
				m_a{alpha}
			{this->generate_hex();}

			color_rgb(const std::string& hex_str) :
				m_hex{hex_str}
			{this->init_from_hex(hex_str);}			

		public:
			std::uint8_t red() const noexcept
			{return m_r;}

			std::uint8_t green() const noexcept
			{return m_g;}

			std::uint8_t blue() const noexcept
			{return m_b;}

			std::uint8_t alpha() const noexcept
			{return m_a;}

			std::string hex() const noexcept
			{return m_hex;}

			const std::uint8_t& r{m_r};
			const std::uint8_t& g{m_g};
			const std::uint8_t& b{m_b};
			const std::uint8_t& a{m_a};

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

			void generate_hex()
			{
				std::ostringstream strm;
				strm << std::setfill('0') << std::hex <<
						std::setw(2) << static_cast<int>(m_r) <<
						std::setw(2) << static_cast<int>(m_g) <<
						std::setw(2) << static_cast<int>(m_b);
				m_hex = strm.str();
			}
		};
	}
}


#endif // MLK_GRAPHICS_COLOR_H
