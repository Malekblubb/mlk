//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_CONTAINERS_MIXED_CONTAINER_H
#define MLK_CONTAINERS_MIXED_CONTAINER_H


#include "mixed_cnt_type.h"

#include <memory>
#include <map>


namespace mlk
{
	namespace cnt
	{
		class mixed_container
		{
			std::map<std::string, std::shared_ptr<internal::mixed_cnt_type_base>> m_vec; // TODO: c++14 replace with std::unique_ptr

		public:
			template<typename T>
			void add(const std::string& key, const T& var)
			{m_vec[key] = std::make_shared<internal::mixed_cnt_type<T>>(internal::mixed_cnt_type<T>{var});}

			template<typename T>
			T get(const std::string& key)
			{return std::static_pointer_cast<internal::mixed_cnt_type<T>>(m_vec[key])->m_var;}
		};
	}
}


#endif // MLK_CONTAINERS_MIXED_CONTAINER_H
