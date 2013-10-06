//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_NETWORK_PACKET_H
#define MLK_NETWORK_PACKET_H


#include "address.h"

#include <vector>


namespace mlk
{
	namespace ntw
	{		
		class packet
		{
			using data_c = std::vector<unsigned char>;

			ip_address m_addr;
			data_c m_data;

		public:
			packet(const ip_address& to, const data_c& data) :
				m_addr{to},
				m_data{data}
			{ }

			ip_address addr() const noexcept {return m_addr;}
			data_c data() const noexcept {return m_data;}
			size_t size() const noexcept {return m_data.size();}

			void clear() {m_data.clear();}
			void add(const data_c& data)
			{
				if(data.size() <= 0)
					return;

				m_data.insert(m_data.end(), data.begin(), data.end());
			}
		};
	}
}


#endif // MLK_NETWORK_PACKET_H
