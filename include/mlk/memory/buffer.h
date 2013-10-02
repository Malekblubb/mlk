//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_MEMORY_BUFFER_H
#define MLK_MEMORY_BUFFER_H

#include <iostream>
#include <cstring>

namespace mlk
{
	namespace memory
	{

		// use for memorybuffers like char, unsigned char
		template<typename T> class buffer
		{
			using buffer_t = T;

			size_t m_bufferSize{0};
			buffer_t* m_buf{nullptr};
			bool m_isAlloced{false};


		public:
			buffer() = default;

			buffer(size_t allocsize) :
				m_bufferSize{allocsize},
				m_buf{new buffer_t[m_bufferSize]},
				m_isAlloced{true} {}

			buffer(buffer_t* buf, size_t buffersize) :
				m_bufferSize{buffersize},
				m_buf{new buffer_t[m_bufferSize]},
				m_isAlloced{true}
			{
				std::memcpy(m_buf, buf, m_bufferSize);
			}

			buffer(const buffer& o) :
				m_bufferSize{o.m_bufferSize},
				m_buf{new buffer_t[m_bufferSize]},
				m_isAlloced{true}
			{
				std::memcpy(m_buf, o.m_buf, m_bufferSize);
			}

			buffer& operator=(const buffer& o)
			{
				delete m_buf;
				m_bufferSize = o.m_bufferSize;
				m_buf = new buffer_t[m_bufferSize];
				std::memcpy(m_buf, o.m_buf, m_bufferSize);
				m_isAlloced = true;
			}

			buffer(buffer&& o) :
				m_bufferSize{o.m_bufferSize},
				m_buf{o.m_buf},
				m_isAlloced{true}
			{
				o.m_buf = nullptr;
			}

			buffer& operator=(buffer&& o)
			{
				delete m_buf;
				m_bufferSize = o.m_bufferSize;
				m_buf = o.m_buf;
				o.m_buf = nullptr;
				m_isAlloced = true;
			}

			~buffer() {delete[] m_buf; m_buf = nullptr;}



			void alloc(size_t allocsize)
			{
				if(!m_isAlloced && (allocsize > 0))
				{
					m_bufferSize = allocsize;
					m_buf = new buffer_t[m_bufferSize];
					m_isAlloced = true;
				}
			}

			buffer_t& operator[](size_t pos)
			{
				if(m_isAlloced && (pos < m_bufferSize))
					return m_buf[pos];

				return m_buf[0]; // TODO: what should i return here ??
			}
		};
	}
}




#endif // MLK_MEMORY_BUFFER_H
