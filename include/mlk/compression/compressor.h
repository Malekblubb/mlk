//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_COMPRESSION_COMPRESSOR_H
#define MLK_COMPRESSION_COMPRESSOR_H


#include <mlk/types/types.h>

#include <cstdint>
#include <vector>


namespace mlk
{
	namespace cmprs
	{
		enum class cmprs_mode : char
		{
			zlib = 0
		};

		namespace internal
		{
			class compressor_base
			{
			protected:
				uint64_t m_input_datasize;
				data_packet m_work_data;

			public:
				compressor_base(const data_packet& data) :
					m_input_datasize{data.size()},
					m_work_data{data}
				{
					m_work_data.shrink_to_fit(); // just to be sure
				}

				virtual int64_t pack() = 0;
				virtual int64_t unpack(uint64_t unpacked_size) = 0;

				virtual const data_packet& get() const noexcept = 0;
			};
		}

		template<cmprs_mode mode>
		class compressor;
	}
}


#endif // MLK_COMPRESSION_COMPRESSION_H
