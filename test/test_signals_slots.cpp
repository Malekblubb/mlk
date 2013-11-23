#include <mlk/signals_slots/signals_slots.h>

#include <iostream>


class my_handle_class
{
	int m_some_member;

public:
	mlk::signal m_some_action_done; // create a signal

	void do_work() noexcept
	{
		m_some_member = 555;
		mlk::emit_signal(m_some_action_done, m_some_member); // call all slots of signal 'm_some_action_done'
	}
};


class my_wrapper
{
	my_handle_class m_handle;
	mlk::slot<int> m_on_action_done{[](int i){std::cout << "test " << i << std::endl;}}; // create a slot that takes an int as parameter

public:
	my_wrapper()
	{
		mlk::link_signal(m_handle.m_some_action_done, m_on_action_done); // link the handler signal to our slot
	}

	// interface
	void start_work()
	{m_handle.do_work();}

	// add a user function
	void add_on_action(const std::function<void(int)>& func)
	{mlk::link_signal(m_handle.m_some_action_done, mlk::slot<int>{func});}
};


void my_external_func(int i)
{std::cout << i/2 << std::endl;}



int main()
{
	my_wrapper w;
	w.add_on_action(my_external_func);
	w.start_work();
}
