//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_SIGNALS_SLOTS_SLOT_H
#define MLK_SIGNALS_SLOTS_SLOT_H


#include <functional>
#include <vector>


namespace mlk
{

	namespace internal
	{class global_signal_handler;}

	template<typename T>
	class slot
	{
		std::vector<std::function<T>> m_funcs;
		bool m_func_set{false};
		friend class internal::global_signal_handler;

	public:
		slot() = default;

		template<typename E>
		void add_func(E func) // non const ref for lambda support
		{m_funcs.push_back(func); m_func_set = true;}

		template<typename E>
		void operator+=(E func)
		{this->add_func(func);}

	private:
		template<typename... M>
		void call_funcs(M... args)
		{
			if(m_func_set)
				for(auto& a : m_funcs)
					a(args...);
		}
	};
}


#endif // MLK_SIGNALS_SLOTS_SLOT_H
