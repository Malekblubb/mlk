//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_NETWORK_PACKET_H
#define MLK_NETWORK_PACKET_H


#include <vector>


namespace mlk
{
	namespace ntw
	{
		class packet
		{
			using data_c = std::vector<unsigned char>;

			data_c m_data;

		public:
			packet(const data_c& data) :
				m_data(data)
			{ }

			data_c data() const noexcept {return m_data;}

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
