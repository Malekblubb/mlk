//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_SIGNALS_SLOTS_SLOT_H
#define MLK_SIGNALS_SLOTS_SLOT_H


#include <functional>
#include <map>
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

			virtual std::size_t num_args() const noexcept = 0;
		};
	}


	template<typename... T>
	class slot : public internal::basic_slot
	{
		std::vector<std::function<void(T...)>> m_funcs;
		static constexpr std::size_t m_num_args{sizeof...(T)};
		friend class internal::global_signal_handler;

	public:
		slot() = default;

		slot(const std::function<void(T...)>& func) :
			m_funcs{func}
		{ }

		~slot() = default;

		template<typename Func>
		void add_func(Func&& func)
		{m_funcs.push_back(func);}

		template<typename Func>
		void operator+=(Func&& func)
		{this->add_func(func);}

		template<typename Func>
		void operator=(Func&& func)
		{
			this->clear();
			this->add_func(func);
		}

		void clear() noexcept
		{m_funcs.clear();}

		std::size_t num_args() const noexcept override
		{return m_num_args;}

		void operator()(const T&... args) const
		{this->call_funcs(args...);}

	private:
		void call_funcs(const T&... args) const
		{
			for(auto& a : m_funcs)
				a(args...);
		}
	};

	template<typename T, typename... SlotTypes>
	using event_delegates = std::map<T, slot<SlotTypes...>>;
}


#endif // MLK_SIGNALS_SLOTS_SLOT_H
