//
// Copyright (c) 2013-2017 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_COMPRESSION_ZLIB_MODE_H
#define MLK_COMPRESSION_ZLIB_MODE_H

#include "compressor.h"

#include <mlk/log/log.h>

#include <zlib.h>

namespace mlk
{
	namespace cmprs
	{
		template <>
		class compressor<cmprs_mode::zlib> : public internal::compressor_base
		{
		public:
			compressor(const data_packet& data) : compressor_base{data} {}

			std::int64_t pack() override
			{
				this->reset_error();
				long unsigned int bound{compressBound(m_input_datasize)};
				data_packet tmp(bound);

				int z_error{compress(reinterpret_cast<Bytef*>(&tmp[0]), &bound,
									 reinterpret_cast<Bytef*>(&m_work_data[0]),
									 m_work_data.size())};

				if(z_error != Z_OK) {
					lerr()["mlk::cmprs::compressor<zlib>"]
						<< "error while compress data. zlib returned: "
						<< z_error;
					this->set_error(z_error);
					return z_error;
				}

				m_work_data = tmp;
				return m_work_data.size();
			}

			std::int64_t unpack(long unsigned int unpacked_size) override
			{
				this->reset_error();
				data_packet tmp(unpacked_size);

				int z_error{uncompress(
					reinterpret_cast<Bytef*>(&tmp[0]), &unpacked_size,
					reinterpret_cast<Bytef*>(&m_work_data[0]),
					m_work_data.size())};

				if(z_error != Z_OK) {
					lerr()["mlk::cmprs::compressor<zlib>"]
						<< "error while uncompress data. zlib returned: "
						<< z_error;
					this->set_error(z_error);
					return z_error;
				}

				m_work_data = tmp;
				return m_work_data.size();
			}

			const data_packet& get() const noexcept override
			{
				return m_work_data;
			}
		};
	}
}

#endif// MLK_COMPRESSION_ZLIB_MODE_H
