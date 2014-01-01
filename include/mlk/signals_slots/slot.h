//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_SIGNALS_SLOTS_SLOT_H
#define MLK_SIGNALS_SLOTS_SLOT_H


#include <functional>
#include <utility>
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


	template<typename Ret, typename... Args>
	class slot : public internal::basic_slot
	{
		static constexpr std::size_t m_num_args{sizeof...(Args)};
		typedef Ret(*fn_ptr)(Args...);
		std::vector<fn_ptr> m_funcs;

		friend class internal::global_signal_handler;

	public:
		slot() = default;

		slot(fn_ptr&& func) :
			m_funcs{func}
		{ }

		~slot() = default;

		void operator()(Args&&... args) const
		{for(auto& a : m_funcs) a(std::forward<Args>(args)...);}

		void add_func(fn_ptr&& func) noexcept
		{m_funcs.push_back(func);}

		void operator+=(fn_ptr&& func) noexcept
		{this->add_func(func);}

		std::size_t num_args() const noexcept override
		{return m_num_args;}

	};
}


#endif // MLK_SIGNALS_SLOTS_SLOT_H
