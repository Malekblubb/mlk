//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_TIME_SIMPLE_TIMER_H
#define MLK_TIME_SIMPLE_TIMER_H


#include "time_utl.h"


namespace mlk
{
	namespace tm
	{
		class simple_timer
		{
			ullong m_interval;
			hrs_time_pnt m_start;
			bool m_running{false};

		public:
			simple_timer(ullong interval) :
				m_interval{interval}
			{ }

			void run() noexcept
			{
				m_running = true;
				m_start = time_pnt();
			}

			void restart(ullong interval) noexcept
			{m_interval = interval; this->run();}

			auto elapsed_time() const noexcept
			-> decltype(duration_to_now(m_start))
			{return duration_to_now(m_start);}

			bool timed_out() const noexcept
			{
				if(!m_running) return false;
				return tm::timed_out(m_start, m_interval);
			}
		};
	}
}


#endif // MLK_TIME_SIMPLE_TIMER_H
