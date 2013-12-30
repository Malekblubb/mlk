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
	namespace cnt
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

		// creates a new object with type 'T
		// from/to the given iterators
		template<typename T>
		T cut_vec(const typename T::const_iterator& from,
				  const typename T::const_iterator& to)
		{return T{from, to};}

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

		// non-const
		template<typename T, typename E>
		auto find_in(const T& value, E& cnt)
		-> decltype(std::find(cnt.begin(), cnt.end(), value))
		{return std::find(cnt.begin(), cnt.end(), value);}

		template<typename T, typename E>
		auto find_in_if(const T& pred, const E& cnt)
		-> decltype(std::find_if(cnt.begin(), cnt.end(), pred))
		{return std::find_if(cnt.begin(), cnt.end(), pred);}

		// non-const
		template<typename T, typename E>
		auto find_in_if(const T& pred, E& cnt)
		-> decltype(std::find_if(cnt.begin(), cnt.end(), pred))
		{return std::find_if(cnt.begin(), cnt.end(), pred);}


		// checks if 'value' exists in 'cnt'
		template<typename T, typename E>
		bool exists(const T& value, const E& cnt)
		{return find_in(value, cnt) != cnt.end();}

		template<typename T, typename E>
		bool exists_if(const T& pred, const E& cnt)
		{return find_in_if(pred, cnt) != cnt.end();}

		// returns true if at least one element of 'find_one'
		// is found in 'in'
		template<typename T, typename E>
		bool match_one(const T& find_one, const E& in)
		{
			for(auto& a : find_one)
				if(find_in(a, in) != in.end())
					return true;
			return false;
		}

		// appends elements of 'app'
		// to 'to'
		// NOTICE: 2 different types:
		// append std::string to mlk::data_packet works
		template<typename T, typename E>
		void append(const T& app, E& to)
		{to.insert(to.end(), app.begin(), app.end());}

		// returns the count of 'value' in 'in'
		template<typename T>
		auto count_of(const T& value, const std::vector<T>& in)
		-> decltype(std::count(in.begin(), in.end(), value))
		{return std::count(in.begin(), in.end(), value);}

		// returns true if element 'value' exists
		// multiple times in 'vec'
		template<typename T>
		bool exists_multiple(const T& value, const std::vector<T>& vec)
		{return count_of(value, vec) > 1;}

		// removes all found elements 'value' in 'vec'
		// but keeps 'num_not' elements
		template<typename T>
		void remove_but(int num_not, const T& value, std::vector<T>& vec)
		{
			auto work_count(count_of(value, vec));
			auto count(work_count);
			vec.erase(std::remove_if(vec.begin(), vec.end(),
			[&](const T& t)
			{return (t == value) && (--work_count < count - num_not);}), vec.end());
		}

		// removes all elements that exists
		// multiple times in 'vec'
		template<typename T>
		void remove_multiple_but_one(std::vector<T>& vec)
		{
			for(auto& a : vec)
				if(exists_multiple(a, vec))
					remove_but(1, a, vec);
		}

		// removes all elements matching 'value'
		// in 'vec'
		template<typename T>
		void remove_all(const T& value, std::vector<T>& vec)
		{remove_but(0, value, vec);}
	}
}


#endif // MLK_CONTAINERS_CONTAINER_UTL_H
