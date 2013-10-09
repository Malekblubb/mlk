//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_CONTAINERS_MIXED_CONTAINER_H
#define MLK_CONTAINERS_MIXED_CONTAINER_H


#include "mixed_cnt_type.h"

#include <string>
#include <memory>
#include <vector>
#include <map>


namespace mlk
{
	namespace cnt
	{
		class mixed_container
		{
		public:
			std::map<std::string, std::shared_ptr<mixed_cnt_type_base>> m_vec;

		public:
			template<typename T>
			void add(const std::string& key, const mixed_cnt_type<T>& var)
			{
				auto ptr = std::make_shared<mixed_cnt_type<T>>(var);
				m_vec[key] = ptr;
			}

			template<typename T>
			T at(std::string key)
			{
				return std::static_pointer_cast<mixed_cnt_type<T>>(m_vec[key])->m_var;
			}
		};
	}
}



#endif // MLK_CONTAINERS_MIXED_CONTAINER_H
