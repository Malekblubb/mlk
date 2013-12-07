//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_CONTAINERS_CONTAINER_UTL_H
#define MLK_CONTAINERS_CONTAINER_UTL_H


#include <mlk/tools/type_utl.h>

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
	namespace cnt // TODO: do utils with iterators
	{
		template<typename T>
		bool is_out_of_bounds(const std::vector<T>& vec, std::size_t index)
		{return index >= vec.size();}

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

			std::vector<T> new_vec(to - from);
			std::copy(source.begin() + from, source.begin() + to, new_vec.begin());
			return new_vec;
		}

		// creates an int out of 4 chars
		// works on little endian
		template<typename T>
		int make_int(int begin, const std::vector<T>& vec)
		{
			static_assert(type_utl::is_char<T>(), "only char types allowed");

			if(is_out_of_bounds(vec, begin + 3))
				return -1;

			int result{0};
			result |= (vec[begin]);
			result |= (vec[begin + 1] << 8);
			result |= (vec[begin + 2] << 16);
			result |= (vec[begin + 3] << 24);
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

		// return true if at least one element of 'find_one'
		// is found in 'in'
		template<typename T, typename E>
		bool match_one(const T& find_one, const E& in)
		{
			for(auto& a : find_one)
				if(std::find(in.begin(), in.end(), a) != in.end())
					return true;
			return false;
		}

		// appends elements of 'app'
		// to 'to'
		template<typename T, typename E>
		void append(const T& app, E& to)
		{std::copy(app.begin(), app.end(), std::back_inserter<E>(to));}
	}
}


#endif // MLK_CONTAINERS_CONTAINER_UTL_H
