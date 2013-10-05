//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_LOG_LOG_H
#define MLK_LOG_LOG_H


#include <mlk/console/console.h>

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


		template<log_level level> class log_base;

		template<> class log_base<log_level::normal>
		{
		protected:
			bool m_saveHistory, m_writeOnExit;
			std::string m_savePath;
			std::ostringstream m_history;

		public:
			log_base() = default;
			log_base(bool saveHistory, bool writeOnExit, const std::string& savePath) :
				m_saveHistory{saveHistory},
				m_writeOnExit{writeOnExit},
				m_savePath{savePath} {}
			~log_base();

			void setSavePath(const std::string& path) {m_savePath = path;}
			void setSaveHistory(bool b) {m_saveHistory = b;}
			void setWriteOnExit(bool b) {m_writeOnExit = b;}

			template<typename T> inline log_base& operator()(const T& val)
			{
				console::reset_color();

				std::ostringstream tmp;
				tmp << "\n[" << val << "] ";

				this->brace_operator_impl(tmp.str());
				return *this;
			}

			template<typename T> log_base& operator<<(const T& val)
			{
				std::cout << val;

				if(m_saveHistory)
					m_history << val;

				return *this;
			}

		protected:
			void brace_operator_impl(const std::string& str)
			{
				std::cout << str;

				if(m_saveHistory)
					m_history << str;
			}
		};

		template<> class log_base<log_level::debug> : public log_base<log_level::normal>
		{
		public:
			log_base(bool saveHistory, bool writeOnExit, const std::string& savePath) :
				log_base<log_level::normal>::log_base{saveHistory, writeOnExit, savePath}{}

			template<typename T> log_base &operator()(const T& val)
			{
				console::set_color(console::console_color::white);

				std::ostringstream tmp;
				tmp << "\n[Debug in fnc: " << val << "] ";

				this->brace_operator_impl(tmp.str());
				return *this;
			}
		};

		template<> class log_base<log_level::internal_error> : public log_base<log_level::normal>
		{
		public:
			log_base(bool saveHistory, bool writeOnExit, const std::string& savePath) :
				log_base<log_level::normal>::log_base{saveHistory, writeOnExit, savePath} {}

			template<typename T> log_base& operator()(const T& val)
			{
				console::set_color(console::console_color::red);

				std::ostringstream tmp;
				tmp << "\n[Error #" << val << "] ";

				this->brace_operator_impl(tmp.str());
				return *this;
			}
		};
	}

	// standard options (can be changed)
	static logger::log_base<logger::log_level::normal> lout{true, true, "./log.log"};
	static logger::log_base<logger::log_level::debug> ldbg{false, false, "./debug.log"};
	static logger::log_base<logger::log_level::internal_error> lerr{true, false, "./error.log"};

	#ifdef DBG
	#undef DBG
	#endif
	#define DBG(x) ldbg(__PRETTY_FUNCTION__) << x
}


#endif // MLK_LOG_LOG_H
