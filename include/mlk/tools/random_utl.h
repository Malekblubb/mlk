//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_TOOLS_RANDOM_UTL_H
#define MLK_TOOLS_RANDOM_UTL_H


#include <mlk/time/time_utl.h>

#include <random>
#include <type_traits>


namespace mlk
{
	namespace internal
	{
		// one instance per run
		inline std::mt19937& rnd_engine_i()
		{
			static std::mt19937 rnd_engine{mlk::tm::time_stmp<std::chrono::nanoseconds>()}; // seed with current nanoseconds
			return rnd_engine;
		}

		template<typename T, bool integral>
		struct rnd_helper
		{
			T operator()(T min, T max)
			{return std::uniform_int_distribution<T>{min, max}(internal::rnd_engine_i());}
		};

		template<typename T>
		struct rnd_helper<T, false>
		{
			static_assert(std::is_floating_point<T>(), "T must be a floating point type");

			T operator()(T min, T max)
			{return std::uniform_real_distribution<T>{min, max}(internal::rnd_engine_i());}
		};
	}

	template<typename T = int>
	T rnd(T min, T max)
	{
		if(min > max)
			throw std::range_error{"'min' must be less than 'max'"};
		return internal::rnd_helper<T, std::is_integral<T>::value>{}(min, max);
	}
}


#endif // MLK_TOOLS_RANDOM_UTL_H
