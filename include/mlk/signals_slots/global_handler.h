//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_SIGNALS_SLOTS_GLOBAL_HANDLER_H
#define MLK_SIGNALS_SLOTS_GLOBAL_HANDLER_H


#include "signal.h"
#include "slot.h"

#include <mlk/containers/container_utl.h>
#include <mlk/log/log_impl.h>

#include <map>
#include <vector>

#include <boost/any.hpp>


namespace mlk
{
	namespace internal
	{
		class global_signal_handler
		{
			// a signal can have one or more slots
			// every slot of "signal" is called, when "signal" is called
			// TODO: make this work for different arguments and returntyped (void())
			std::map<signal, std::vector<slot<void()>>> m_content;
			int m_current_uid{1};
			std::vector<int> m_linked_uids;

		public:
			template<typename T>
			void link_signal(signal& si, const slot<T>& sl)
			{
				// if signal is already registered, skip new register
				if(std::find(m_linked_uids.begin(), m_linked_uids.end(), si.m_uid) == m_linked_uids.end())
				{
					si.m_uid = m_current_uid; // signal gets new id
					m_linked_uids.push_back(m_current_uid); // add to linked uids
					++m_current_uid; // create new uid
				}
				// this signal is invalid
				if(si.m_uid == 0)
					return;

				// add slot to registered signal
				m_content[si].push_back(sl);
			}

			template<typename... E>
			void emit_signal(const signal& si, E... args)
			{
				if(m_content.find(si) == m_content.end())
				{
					lerr() << "warning: signal with uid " << si.m_uid << " not found, ignoring call";
					return;
				}

				for(auto& a : m_content[si])
					a.call_funcs(args...);
			}
		};

		static global_signal_handler gsh; // global instance
	}


	// functions to link and emit signals and slots
	template<typename T>
	void link_signal(signal& si, const slot<T>& sl)
	{internal::gsh.link_signal(si, sl);}

	template<typename... E>
	void emit_signal(const signal& si, E... args)
	{internal::gsh.emit_signal(si, args...);}
}


#endif // MLK_SIGNALS_SLOTS_GLOBAL_HANDLER_H
