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
	{
		class global_signal_handler;

		class basic_slot
		{
		public:
			virtual ~basic_slot() = default;
		};
	}


	template<typename... T>
	class slot : public internal::basic_slot
	{
		std::vector<std::function<void(T...)>> m_funcs;
		friend class internal::global_signal_handler;

	public:
		slot() = default;

		slot(const std::function<void(T...)>& func) :
			m_funcs{func}
		{ }

		~slot() = default;

		void add_func(const std::function<void(T...)>& func)
		{m_funcs.push_back(func);}

		void operator+=(const std::function<void(T...)>& func)
		{this->add_func(func);}


	private:
		bool has_funcs() const noexcept {return !m_funcs.empty();}

		void call_funcs(T... args)
		{
			if(has_funcs())
				for(auto& a : m_funcs)
					a(args...);
		}
	};
}


#endif // MLK_SIGNALS_SLOTS_SLOT_H
