//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_LOG_ERROR_HANDLER_H
#define MLK_LOG_ERROR_HANDLER_H


#include <mlk/containers/error_container.h>


namespace mlk
{
	namespace logger
	{
		namespace internal
		{
			class error_handler
			{
				cnt::error_container m_cnt;

			public:
				void set_error_container(const cnt::error_container& cnt)
				{
					m_cnt = cnt;
				}

				template<typename T>
				void try_call(const T& error_code)
				{
					int index{m_cnt.find(error_code)};
					if(index != -1)
						m_cnt.get(index)->call();
				}
			};
		}
	}
}



#endif // MLK_LOG_ERROR_HANDLER_H
