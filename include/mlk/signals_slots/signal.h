//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_SIGNALS_SLOTS_SIGNAL_H
#define MLK_SIGNALS_SLOTS_SIGNAL_H


namespace mlk
{
	namespace internal
	{class global_signal_handler;}

	class signal
	{
		int m_uid{0};
		bool m_registered{false};
		inline friend bool operator<(const signal&, const signal&);
		friend class internal::global_signal_handler;
	};

	inline bool operator<(const signal& l, const signal& r)
	{return l.m_uid < r.m_uid;}
}


#endif // MLK_SIGNALS_SLOTS_SIGNAL_H
