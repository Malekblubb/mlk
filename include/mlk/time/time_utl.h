//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_TIME_TIME_UTL_H
#define MLK_TIME_TIME_UTL_H


#include <mlk/types/types.h>

#include <chrono>
#include <string>
#include <thread>


namespace mlk
{
	namespace tm
	{
		template<typename T = micro_s>
		ullong time_stmp()
		{
			return std::chrono::duration_cast<seconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() +
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

		inline auto sys_time_pnt()
		-> decltype(std::chrono::system_clock::now())
		{return std::chrono::system_clock::now();}

		template<typename T = milli_s, typename E>
		auto duration(const std::chrono::time_point<E>& start, const std::chrono::time_point<E>& end)
		-> decltype(std::chrono::duration_cast<T>(end-start).count())
		{return std::chrono::duration_cast<T>(end-start).count();}

		template<typename T, typename E = std::milli, typename M>
		auto duration_as(const std::chrono::time_point<M>& start, const std::chrono::time_point<M>& end)
		-> decltype(duration<std::chrono::duration<T, E>>(start, end))
		{return duration<std::chrono::duration<T, E>>(start, end);}

		// return the duration to now
		// starting by 'start'
		template<typename T = milli_s, typename E>
		auto duration_to_now(const std::chrono::time_point<E>& start)
		-> decltype(duration<T>(start, time_pnt()))
		{return duration<T>(start, time_pnt());}

		// returns true when the duration of 'start_pnt' and now is >= 'max'
		template<typename T = milli_s>
		bool timed_out(const decltype((std::chrono::high_resolution_clock::now())) start_pnt, llong max)
		{return duration<T>(start_pnt, time_pnt()) >= max;}

		template<typename T = milli_s>
		void sleep(llong time)
		{std::this_thread::sleep_for(T(time));}
	}
}


#endif // MLK_TIME_TIME_UTL_H
