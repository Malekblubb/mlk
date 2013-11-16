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


	namespace internal
	{
		class basic_slot
		{
		public:
			virtual ~basic_slot() = default;
		};
	}


	template<typename T = void()>
	class slot : public internal::basic_slot
	{
		std::vector<std::function<T>> m_funcs;
		friend class internal::global_signal_handler;

	public:
		slot() = default;

		template<typename E>
		slot(E func) :
			m_funcs{func}
		{ }

		~slot() = default;

		template<typename E>
		void add_func(E func) // non const ref for lambda support
		{m_funcs.push_back(func);}

		template<typename E>
		void operator+=(E func)
		{this->add_func(func);}


	private:
		bool has_funcs() const noexcept {return !m_funcs.empty();}

		template<typename... M>
		void call_funcs(M... arg)
		{
			if(has_funcs())
				for(auto& a : m_funcs)
					a(arg...);
		}
	};
}


#endif // MLK_SIGNALS_SLOTS_SLOT_H
