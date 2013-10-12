//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_CONTAINERS_CONTAINER_UTL_H
#define MLK_CONTAINERS_CONTAINER_UTL_H


#include <vector>


namespace mlk
{
	namespace cnt
	{
		template<typename T>
		bool is_out_of_bounds(const std::vector<T>& vec, int index)
		{
			return (index >= vec.size()) || (index < 0);
		}
	}
}


#endif // MLK_CONTAINERS_CONTAINER_UTL_H
