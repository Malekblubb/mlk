//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_NETWORK_PACKET_H
#define MLK_NETWORK_PACKET_H


#include "address.h"

#include <mlk/log/log.h>
#include <mlk/tools/type_utl.h>
#include <mlk/types/types.h>

#include <vector>


namespace mlk
{
	namespace ntw
	{		
		class packet
		{
			ip_address m_addr{"0.0.0.0", 0};
			data_packet m_data;

		public:
			packet(const data_packet& data) :
				m_data{data}
			{ }

			packet(const ip_address& to, const data_packet& data) :
				m_addr{to},
				m_data{data}
			{ }

			void set_address(const ip_address& addr) noexcept {m_addr = addr;}

			const ip_address& addr() const noexcept {return m_addr;}
			const data_packet& data() const noexcept {return m_data;}
			size_t size() const noexcept {return m_data.size();}

			void clear() noexcept {m_data.clear();}

			template<typename T>
			const packet& append(const T& app)
			{
				static_assert(std::is_same<T, mlk::data_packet>() ||
							  type_utl::is_str<T>(), "string or mlk::data_packet required");
				if(app.size() <= 0)
				{
					lerr()["mlk::ntw::packet"] << "data with invalid size passed";
					return *this;
				}
				cnt::append(app, m_data);
				return *this;
			}
		};
	}
}


#endif // MLK_NETWORK_PACKET_H
