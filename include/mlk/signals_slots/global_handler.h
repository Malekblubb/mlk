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

		public:
			static global_signal_handler& instance()
			{
				static global_signal_handler instance;
				return instance;
			}

			template<typename... T>
			void link_signal(signal& si, const slot<T...>& sl)
			{
				// if signal is already registered, skip new register
				if(!si.m_registered)
				{
					si.m_uid = m_current_uid; // signal gets new id
					si.m_registered = true;
					++m_current_uid; // create new uid
				}

				// add slot to registered signal
				m_content[si].push_back(std::make_shared<slot<T...>>(sl));
			}

			template<typename... E>
			void emit_signal(const signal& si, E... args)
			{
				if(!si.m_registered) // signal not found
					return;

				for(auto& a : m_content[si])
					std::static_pointer_cast<slot<E...>>(a)->call_funcs(args...);
			}
		};
	}


	// functions to link and emit signals and slots
	template<typename... T>
	void link_signal(signal& si, const slot<T...>& sl)
	{internal::global_signal_handler::instance().link_signal(si, sl);}

	template<typename... E>
	void emit_signal(const signal& si, E... args)
	{internal::global_signal_handler::instance().emit_signal(si, args...);}
}


#endif // MLK_SIGNALS_SLOTS_GLOBAL_HANDLER_H
