//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_TOOLS_RANDOM_UTL_H
#define MLK_TOOLS_RANDOM_UTL_H


#include <mlk/time/time_utl.h>

#include <random>


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
	}

	template<typename T = int>
	T rnd(T min, T max)
	{
		if(min > max)
			return 0;
		return std::uniform_int_distribution<T>{min, max}(internal::rnd_engine_i());
	}
}


#endif // MLK_TOOLS_RANDOM_UTL_H
