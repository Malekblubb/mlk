//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_CONTAINERS_ERROR_CONTAINER_H
#define MLK_CONTAINERS_ERROR_CONTAINER_H


#include "error_type.h"

#include <memory>
#include <vector>


namespace mlk
{
	namespace cnt
	{
		class error_container
		{
			std::vector<std::shared_ptr<error_type_base>> m_errors;

		public:

			template<typename T>
			void link(const T& error_code, const std::string& msg, std::function<void()> fnc)
			{
				m_errors.push_back(std::make_shared<error_type<T>>(error_type<T>{error_code, msg, fnc}));
			}

			template<typename T>
			int find(const T& error_code)
			{
				int index{0};
				for(auto& a : m_errors)
				{
					if(std::static_pointer_cast<error_type<T>>(a)->cmp_code(error_code))
						return index;
					++index;
				}
				return -1;
			}

			template<typename T>
			std::shared_ptr<error_type<T>> get_casted(int index) const
			{
				return std::static_pointer_cast<error_type<T>>(m_errors[index]);
			}

			std::shared_ptr<error_type_base> get(int index) const
			{
				return m_errors[index];
			}
		};
	}
}



#endif // MLK_CONTAINERS_ERROR_CONTAINER_H
