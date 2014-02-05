//
// Copyright (c) 2013-2014 Christoph Malek
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
				{m_cnt = cnt;}

				template<typename T>
				void try_call(T error_code) const noexcept
				{
					int index{m_cnt.find(error_code)};
					if(index != -1)
						m_cnt.get(index)->call();
				}

				template<typename T>
				std::string error_str(T error_code) const noexcept
				{
					int index{m_cnt.find(error_code)};
					if(index != -1)
						return m_cnt.get(index)->msg();

					return "";
				}

				template<typename T>
				void link_error(T error_code, const std::string& msg, const mlk::slot<void>& fnc = {[]{}})
				{m_cnt.link(error_code, msg, fnc);}

				template<typename T>
				void link_error(const cnt::error_type<T>& error)
				{m_cnt.link(error);}

				template<typename T>
				cnt::error_type<T> get_error(T error_code) const noexcept
				{
					auto index(m_cnt.find(error_code));
					if(index == -1)
						throw std::runtime_error{"mlk::[...]::error_handler: error_code not found"};
					return *m_cnt.get_casted<T>(index);
				}
			};
		}
	}
}


#endif // MLK_LOG_ERROR_HANDLER_H
