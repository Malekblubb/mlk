//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_CONTAINERS_ERROR_CONTAINER_H
#define MLK_CONTAINERS_ERROR_CONTAINER_H


#include "container_utl.h"
#include "error_type.h"

#include <memory>
#include <stdexcept>
#include <vector>


namespace mlk
{
	namespace cnt
	{
		class error_container
		{
			std::vector<std::shared_ptr<internal::error_type_base>> m_errors;

		public:
			template<typename T>
            void link(T error_code, const std::string& msg, const mlk::slot<>& fnc = {})
			{m_errors.push_back(std::make_shared<error_type<T>>(error_code, msg, fnc));}

			template<typename T>
			void link(const error_type<T>& error)
			{m_errors.push_back(std::make_shared<error_type<T>>(error));}

			template<typename T>
			int find(T error_code) const
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
				if(is_out_of_bounds(m_errors, index))
					throw std::out_of_range{"mlk::cnt::error_container::get_casted: index was out of bounds"};
				return std::static_pointer_cast<error_type<T>>(m_errors[index]);
			}

			std::shared_ptr<internal::error_type_base> get(int index) const
			{
				if(is_out_of_bounds(m_errors, index))
					throw std::out_of_range{"mlk::cnt::error_container::get: index was out of bounds"};
				return m_errors[index];
			}
		};
	}
}


#endif // MLK_CONTAINERS_ERROR_CONTAINER_H
