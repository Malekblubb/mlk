//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_CONTAINERS_CONTAINER_UTL_H
#define MLK_CONTAINERS_CONTAINER_UTL_H


#include <stdexcept>
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

		// compare lhs and rhs, starting from 'from' end by 'to'
		template<typename T>
		bool vec_cmp(int from, int to, const std::vector<T>& lhs, const std::vector<T>& rhs)
		{
			if(is_out_of_bounds(lhs, to) || is_out_of_bounds(rhs, to))
				return false;

			for(int i{from}; i <= to; ++i)
				if(rhs[i] != lhs[i])
					return false;

			return true;
		}

		// creates a new std::vector<T> from the given source [from, to]
		template<typename T>
		auto cut_vec(int from, int to, const std::vector<T>& source)
		-> std::vector<T>
		{
			if(is_out_of_bounds(source, to))
				throw std::out_of_range("mlk::cnt::cut_vec: out of bounds");

			std::vector<T> new_vec(to - from + 1);
			std::copy(source.begin() + from, source.begin() + to + 1, new_vec.begin());
			return new_vec;
		}
	}
}


#endif // MLK_CONTAINERS_CONTAINER_UTL_H
