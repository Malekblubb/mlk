//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_LOG_LOG_H
#define MLK_LOG_LOG_H


#include "error_handler.h"

#include <mlk/console/console.h>
#include <mlk/tools/enum_utl.h>

#include <iostream>
#include <sstream>
#include <string>


namespace mlk
{
	namespace logger
	{
		enum class log_level : unsigned char
		{
			normal = 0,
			debug,
			internal_error
		};


		template<log_level level>
		class log_base;

		template<>
		class log_base<log_level::normal>
		{
		protected:
			bool m_save_history, m_write_on_exit;
			std::string m_save_path;
			std::ostringstream m_history;

		public:
			log_base() = default;
			log_base(bool save_history, bool write_on_exit, const std::string& save_path) :
				m_save_history{save_history},
				m_write_on_exit{write_on_exit},
				m_save_path{save_path} {}
			~log_base();

			void set_save_path(const std::string& path) {m_save_path = path;}
			void set_save_history(bool b) {m_save_history = b;}
			void set_write_on_exit(bool b) {m_write_on_exit = b;}

			template<typename T>
			log_base& operator()(const T& val)
			{
				console::reset_color();

				std::ostringstream tmp;
				tmp << "\n[" << val << "] ";

				this->brace_operator_impl(tmp.str());
				return *this;
			}

			template<typename T>
			log_base& operator<<(const T& val)
			{
				std::cout << val;

				if(m_save_history)
					m_history << val;

				return *this;
			}

		protected:
			void brace_operator_impl(const std::string& str)
			{
				std::cout << str;

				if(m_save_history)
					m_history << str;
			}
		};

		template<>
		class log_base<log_level::debug> : public log_base<log_level::normal>
		{
		public:
			log_base(bool save_history, bool write_on_exit, const std::string& save_path) :
				log_base<log_level::normal>{save_history, write_on_exit, save_path}
			{ }

			template<typename T>
			log_base& operator()(const T& val)
			{
				console::set_color(console::console_color::white);

				std::ostringstream tmp;
				tmp << "\n[Debug in fnc: " << val << "] ";

				this->brace_operator_impl(tmp.str());
				return *this;
			}
		};

		template<>
		class log_base<log_level::internal_error> :
				public log_base<log_level::normal>,
				public internal::error_handler
		{
		public:
			log_base(bool save_history, bool write_on_exit, const std::string& save_path) :
				log_base<log_level::normal>{save_history, write_on_exit, save_path}
			{ }

			template<typename T>
			log_base& operator()(const T& error_code)
			{
				static_assert(std::is_enum<T>::value ||
							  std::is_integral<T>::value, "enum or integral type required");

				console::set_color(console::console_color::red);

				std::ostringstream tmp;
				tmp << "\n[Error #" << enum_utl::to_int(error_code) << "] " << this->error_str(error_code) << " ";

				this->brace_operator_impl(tmp.str());
				this->try_call(error_code); // call error function if it is available
				return *this;
			}

			log_base& operator()() // empty request
			{
				console::set_color(console::console_color::red);
				this->brace_operator_impl(std::string("\n[Error] "));
				return *this;
			}
		};
	}

	// standard options (can be changed while runtime)
	static logger::log_base<logger::log_level::normal> lout{true, true, "./log.log"};
	static logger::log_base<logger::log_level::debug> ldbg{false, false, "./debug.log"};
	static logger::log_base<logger::log_level::internal_error> lerr{true, false, "./error.log"};

	#ifndef MLK_DBG
	#define MLK_DBG(x) mlk::ldbg(__PRETTY_FUNCTION__) << x
	#endif
}


#endif // MLK_LOG_LOG_H
