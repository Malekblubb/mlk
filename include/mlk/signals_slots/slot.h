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

			virtual int num_args() const noexcept = 0;
		};
	}


	template<typename... T>
	class slot : public internal::basic_slot
	{
		std::vector<std::function<void(T...)>> m_funcs;
		static constexpr int m_num_args{sizeof...(T)};
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

		int num_args() const noexcept override
		{return m_num_args;}

		void operator()(T... args)
		{this->call_funcs(args...);}

	private:
		bool has_funcs() const noexcept
		{return !m_funcs.empty();}

		void call_funcs(T... args)
		{
			if(this->has_funcs())
				for(auto& a : m_funcs)
					a(args...);
		}
	};
}


#endif // MLK_SIGNALS_SLOTS_SLOT_H
