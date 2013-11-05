//
// Copyright (c) 2013 Christoph Malek
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
		template<>
		class compressor<cmprs_mode::zlib> : public internal::compressor_base
		{
		public:
			compressor(const data_packet& data) :
				compressor_base{data}
			{ }

			int64_t pack() override
			{
				uint64_t bound{compressBound(m_input_datasize)};
				data_packet tmp(bound);

				int z_error{compress(reinterpret_cast<Bytef*>(&tmp[0]), &bound,
						reinterpret_cast<Bytef*>(&m_work_data[0]), m_work_data.size())};

				if(z_error != Z_OK)
				{
					lerr()() << "Error while compress data. Zlib returned: " << z_error;
					return z_error;
				}

				m_work_data = tmp;
				return m_work_data.size();
			}

			int64_t unpack(uint64_t unpacked_size) override
			{
				data_packet tmp(unpacked_size);

				int z_error{uncompress(reinterpret_cast<Bytef*>(&tmp[0]), &unpacked_size,
						reinterpret_cast<Bytef*>(&m_work_data[0]), m_work_data.size())};

				if(z_error != Z_OK)
				{
					lerr()() << "Error while uncompress data. Zlib returned: " << z_error;
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



#endif // MLK_COMPRESSION_ZLIB_MODE_H
