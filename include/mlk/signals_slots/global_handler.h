//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_SIGNALS_SLOTS_GLOBAL_HANDLER_H
#define MLK_SIGNALS_SLOTS_GLOBAL_HANDLER_H


#include "signal.h"
#include "slot.h"

#include <mlk/containers/container_utl.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <vector>


namespace mlk
{
	namespace internal
	{
		class global_signal_handler
		{
			// a signal can have one or more slots
			// every slot of "signal" is called, when "signal" is called
			std::map<signal, std::vector<std::shared_ptr<basic_slot>>> m_content;
			int m_current_uid{1};
			std::vector<int> m_linked_uids;

		public:
			static global_signal_handler& instance()
			{
				static global_signal_handler instance;
				return instance;
			}

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
				m_content[si].push_back(std::make_shared<slot<T>>(sl));
			}

			template<typename... E>
			void emit_signal(const signal& si, E... arg)
			{
				if(m_content.find(si) == m_content.end()) // signal not found
				{
					std::cout << "\n[Error] warning: signal with uid " << si.m_uid << " not found, ignoring emit";
					return;
				}

				for(auto& a : m_content[si])
					std::static_pointer_cast<slot<void(E...)>>(a)->call_funcs(arg...);
			}
		};
	}


	// functions to link and emit signals and slots
	template<typename T>
	void link_signal(signal& si, const slot<T>& sl)
	{internal::global_signal_handler::instance().link_signal(si, sl);}

	template<typename... E>
	void emit_signal(const signal& si, E... arg)
	{internal::global_signal_handler::instance().emit_signal(si, arg...);}
}


#endif // MLK_SIGNALS_SLOTS_GLOBAL_HANDLER_H
