//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_TIME_TIMER_H
#define MLK_TIME_TIMER_H


#include "time_utl.h"
#include <mlk/signals_slots/signals_slots.h>
#include <mlk/types/types.h>

#include <future>
#include <iostream>

namespace mlk
{
	namespace tm
	{
		class timer
		{
			ullong m_interval;
			hrs_time_pnt m_start{time_pnt()};
			bool m_running{false};

			std::future<void> m_run_future;

		public:
			signal m_timeout;

			timer(ullong interval_ms) :
				m_interval{interval_ms}
			{ }

			~timer()
			{this->stop();}

			void run() noexcept
			{
				if(m_running)
					return;
				m_start = time_pnt();
				m_running = true;
				this->run_impl();
			}

			void stop() noexcept
			{
				m_running = false;
				if(m_run_future.valid())
					m_run_future.get();
			}

			auto elapsed_time() const noexcept
			-> decltype(duration_to_now(m_start))
			{return duration_to_now(m_start);}

		private:
			void run_impl() noexcept
			{
				m_run_future = std::async(std::launch::async,
				[this]
				{
					while(m_running)
					{
						if(timed_out(m_start, m_interval))
						{
							// signal will be emited in another thread!
							mlk::emit_signal(m_timeout);
							m_start = time_pnt();
						}
					}
				});
			}
		};
	}
}



#endif // MLK_TIME_TIMER_H
