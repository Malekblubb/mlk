//
// Copyright (c) 2013-2017 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_LOG_LOG_IMPL_H
#define MLK_LOG_LOG_IMPL_H

#include "error_handler.h"

#include <mlk/console/console.h>
#include <mlk/signals_slots/signal.h>
#include <mlk/time/time.h>
#include <mlk/tools/enum_utl.h>
#include <mlk/tools/stl_string_utl.h>

#include <iostream>
#include <sstream>
#include <string>

namespace mlk
{
	namespace logger
	{
		enum class log_level : unsigned char
		{
			normal,
			debug,
			internal_error
		};

		template <log_level level>
		class log_base;

		template <>
		class log_base<log_level::normal>
		{
		protected:
			bool m_save_history{false}, m_write_on_exit{false},
				m_show_thread{false}, m_use_flush{true};
			std::string m_save_path;
			std::ostringstream m_history;
			std::ios::openmode m_mode;

		public:
			signal m_entry_added;

			log_base() = default;
			log_base(bool save_history, bool write_on_exit,
					 bool override_old_log, const std::string& save_path);
			~log_base();

			static log_base& instance()
			{
				static log_base instance{true, true, true, "./log.log"};
				return instance;
			}

			template <bool show_thread>
			log_base& st()
			{
				m_show_thread = show_thread;
				return *this;
			}

			void flush() { std::cout.flush(); }

			void set_save_path(const std::string& path) noexcept
			{
				m_save_path = path;
			}
			void set_save_history(bool b) noexcept { m_save_history = b; }
			void set_write_on_exit(bool b) noexcept { m_write_on_exit = b; }
			void set_override_old_log(bool b) noexcept
			{
				b ? m_mode = std::ios::out | std::ios::trunc
				  : m_mode = std::ios::out | std::ios::app;
			}
			void set_use_flush(bool b) noexcept { m_use_flush = b; }

			std::string history() const noexcept { return m_history.str(); }

			template <typename T>
			log_base& operator()(const T& val, bool add_timestamp = false)
			{
				console::reset_color();

				std::ostringstream tmp;
				tmp << "\n";
				if(add_timestamp) tmp << "[" << tm::time_str() << "]";
				if(m_show_thread)
					tmp << "[T:" << std::this_thread::get_id() << "]";

				tmp << "[" << val << "] ";

				this->brace_operator_impl(tmp.str());
				return *this;
			}

			template <typename T>
			log_base& operator<<(const T& val)
			{
				std::cout << val;

				if(m_save_history) m_history << val;

				this->entry_added(stl_string::to_string(val));
				return *this;
			}

		protected:
			void brace_operator_impl(const std::string& str)
			{
				std::cout << str;

				if(m_save_history) m_history << str;
				this->entry_added(str);
			}

			void entry_added(const std::string& last_entry);
		};

		template <>
		class log_base<log_level::debug> : public log_base<log_level::normal>
		{
		public:
			log_base(bool save_history, bool write_on_exit,
					 bool override_old_log, const std::string& save_path)
				: log_base<log_level::normal>{save_history, write_on_exit,
											  override_old_log, save_path}
			{
			}

			static log_base& instance()
			{
				static log_base instance{false, false, true, "./debug.log"};
				return instance;
			}

			// need to override this function
			// because log_base class has no operator[]
			template <bool show_thread>
			log_base& st()
			{
				m_show_thread = show_thread;
				return *this;
			}

			template <typename T>
			log_base& operator()(const T& val, bool add_timestamp = false)
			{
				console::set_color(console::console_color::cyan);

				std::ostringstream tmp;
				tmp << "\n";
				if(add_timestamp) tmp << "[" << tm::time_str() << "]";

				if(m_show_thread)
					tmp << "[T:" << std::this_thread::get_id() << "]";

				tmp << "[Debug in fnc: " << val << "] ";

				this->brace_operator_impl(tmp.str());
				return *this;
			}
		};

		template <>
		class log_base<log_level::internal_error>
			: public log_base<log_level::normal>, public internal::error_handler
		{
		public:
			log_base(bool save_history, bool write_on_exit,
					 bool override_old_log, const std::string& save_path)
				: log_base<log_level::normal>{save_history, write_on_exit,
											  override_old_log, save_path}
			{
			}

			static log_base& instance()
			{
				static log_base instance{true, false, true, "./error.log"};
				return instance;
			}

			// need to override this function
			// because log_base class has no operator[]
			template <bool show_thread>
			log_base& st()
			{
				m_show_thread = show_thread;
				return *this;
			}

			template <typename T>
			log_base& operator()(const T& error_code,
								 bool add_timestamp = false)
			{
				static_assert(std::is_enum<T>() || std::is_integral<T>(),
							  "enum or integral type required");

				console::set_color(console::console_color::red);

				std::ostringstream tmp;
				tmp << "\n";
				if(add_timestamp) tmp << "[" << tm::time_str() << "]";
				if(m_show_thread)
					tmp << "[T:" << std::this_thread::get_id() << "]";

				tmp << "[Error #" << enum_utl::to_int(error_code) << "]"
					<< this->error_str(error_code);

				this->brace_operator_impl(tmp.str());
				this->try_call(
					error_code);// call error function if it is available
				return *this;
			}

			log_base& operator()()// empty request
			{
				console::set_color(console::console_color::red);
				std::ostringstream tmp;
				tmp << "\n[Error]";
				if(m_show_thread)
					tmp << "[T:" << std::this_thread::get_id() << "]";
				this->brace_operator_impl(tmp.str());
				return *this;
			}

			template <typename T>
			log_base& operator[](const T& value)
			{
				std::ostringstream tmp;
				tmp << "[" << value << "] ";
				this->brace_operator_impl(tmp.str());
				return *this;
			}
		};
	}

	template <bool show_thread = true, typename... T>
	logger::log_base<logger::log_level::normal>& lout(T... var)
	{
		return logger::log_base<logger::log_level::normal>::instance()
			.st<show_thread>()(var...);
	}

	template <bool show_thread = true, typename... T>
	logger::log_base<logger::log_level::debug>& ldbg(T... var)
	{
		return logger::log_base<logger::log_level::debug>::instance()
			.st<show_thread>()(var...);
	}

	template <bool show_thread = true, typename... T>
	logger::log_base<logger::log_level::internal_error>& lerr(T... var)
	{
		return logger::log_base<logger::log_level::internal_error>::instance()
			.st<show_thread>()(var...);
	}

	template <typename T = logger::log_base<logger::log_level::normal>>
	T& lout_i()
	{
		return T::instance();
	}

	template <typename T = logger::log_base<logger::log_level::debug>>
	T& ldbg_i()
	{
		return T::instance();
	}

	template <typename T = logger::log_base<logger::log_level::internal_error>>
	T& lerr_i()
	{
		return T::instance();
	}

	// debug

	template <typename Logger>
	void md_impl(Logger&)
	{
	}

	template <typename Logger, typename Head, typename... Tail>
	void md_impl(Logger& dbg_instance, const Head& h, Tail&&... tail)
	{
		dbg_instance << h << " ";
		md_impl(dbg_instance, tail...);
	}

	template <typename... Args>
	void md(const std::string& funcname, Args&&... args)
	{
		auto& dbg_instance(ldbg(funcname));
		md_impl(dbg_instance, args...);
	}

// debug macro which allows miultiple args
#ifndef MD
#define MD(...) mlk::md(__PRETTY_FUNCTION__, __VA_ARGS__)
#endif

// default debug macro
#ifndef MLK_DBG
#define MLK_DBG(x) mlk::ldbg(__PRETTY_FUNCTION__) << x
#endif
}

#endif// MLK_LOG_LOG_IMPL_H
