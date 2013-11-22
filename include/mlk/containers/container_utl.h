//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_CONTAINERS_CONTAINER_UTL_H
#define MLK_CONTAINERS_CONTAINER_UTL_H


#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <vector>


// inserts elements of 'from' to the end of 'result'
template<typename T>
void operator+=(std::vector<T>& result, const std::vector<T>& from)
{result.insert(result.end(), from.begin(), from.end());}

namespace mlk
{
	namespace cnt
	{
		template<typename T>
		bool is_out_of_bounds(const std::vector<T>& vec, std::size_t index)
		{
			return index >= vec.size();
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

		// creates a new std::vector<T> from the given source [from, to)
		template<typename T>
		auto cut_vec(int from, int to, const std::vector<T>& source)
		-> std::vector<T>
		{
			if(is_out_of_bounds(source, to - 1))
				throw std::out_of_range("mlk::cnt::cut_vec: out of bounds");

			std::vector<T> new_vec((to - from) + 1);
			std::copy(source.begin() + from, source.begin() + to, new_vec.begin());
			return new_vec;
		}

		// creates an int out of 4 chars
		// works on little endian
		template<typename T>
		int make_int(int begin, const std::vector<T>& vec) // TODO: add checking for char types
		{
			if(is_out_of_bounds(vec, begin + 3))
				return -1;

			int result{0};
			result |= (vec.data()[begin]);
			result |= (vec.data()[begin + 1] << 8);
			result |= (vec.data()[begin + 2] << 16);
			result |= (vec.data()[begin + 3] << 24);
			return result;
		}

		// if 'value' is found in 'cnt', an iter will be returned
		// to the found element
		template<typename T, typename E>
		auto find_in(const T& value, const E& cnt)
		-> decltype(std::find(cnt.begin(), cnt.end(), value))
		{return std::find(cnt.begin(), cnt.end(), value);}

		template<typename T, typename E>
		auto find_in_if(const T& pred, const E& cnt)
		-> decltype(std::find_if(cnt.begin(), cnt.end(), pred))
		{return std::find_if(cnt.begin(), cnt.end(), pred);}
	}
}


#endif // MLK_CONTAINERS_CONTAINER_UTL_H
