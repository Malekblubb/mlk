//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_TIME_TIME_UTL_H
#define MLK_TIME_TIME_UTL_H


#include <mlk/types/types.h>

#include <chrono>
#include <string>


namespace mlk
{
	namespace tm
	{
		template<typename T = std::chrono::microseconds>
		ullong time_stmp()
		{
			return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() +
					std::chrono::duration_cast<T>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
		}

		inline std::string time_str()
		{
			auto tp = std::chrono::high_resolution_clock::now();
			auto tt = std::chrono::system_clock::to_time_t(tp);
			std::string time{std::ctime(&tt)};
			return time.substr(0, time.length() - 1);
		}

		inline auto time_pnt()
		-> decltype(std::chrono::high_resolution_clock::now())
		{return std::chrono::high_resolution_clock::now();}

		template<typename T = std::chrono::milliseconds, typename E>
		auto duration(const std::chrono::time_point<E>& start, const std::chrono::time_point<E>& end)
		-> decltype(std::chrono::duration_cast<T>(end-start).count())
		{return std::chrono::duration_cast<T>(end-start).count();}

		// returns true when the duration of 'start_pnt' and now is >= 'max'
		template<typename T = std::chrono::milliseconds>
		inline bool timed_out(decltype(std::chrono::high_resolution_clock::now()) start_pnt, llong max)
		{return duration<T>(start_pnt, time_pnt()) >= max;}
	}
}


#endif // MLK_TIME_TIME_UTL_H
