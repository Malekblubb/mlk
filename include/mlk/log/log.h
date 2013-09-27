/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

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


		template<log_level Level> class log_base
		{

		};

		template<> class log_base<log_level::normal>
		{
		protected:
			bool m_saveHistory, m_writeOnExit;
			std::ostringstream m_history;

		public:
			log_base() = default;
			log_base(bool saveHistory, bool writeOnExit) :
				m_saveHistory(saveHistory),
				m_writeOnExit(writeOnExit)
			{

			}

			~log_base()
			{
				console::resetColor();

				if(m_writeOnExit)
				{
					// TODO: writefun
				}
			}

			template<typename T> inline log_base &operator()(const T &val)
			{
				console::resetColor();

				std::ostringstream tmp;
				tmp << "\n[" << val << "] ";

				this->braceOperatorImpl(tmp.str());

				return *this;
			}

			template<typename T> log_base &operator<<(const T &val)
			{
				std::cout << val;

				if(m_saveHistory)
					m_history << val;

				return *this;
			}

		protected:
			void braceOperatorImpl(const std::string &str)
			{
				std::cout << str;

				if(m_saveHistory)
					m_history << str;
			}
		};

		template<> class log_base<log_level::debug> : public log_base<log_level::normal>
		{
		public:
			log_base(bool saveHistory, bool writeOnExit) :
				log_base<log_level::normal>::log_base{saveHistory, writeOnExit} {}

			template<typename T> log_base &operator()(const T &val)
			{
				console::setColor(console::console_color::white);

				std::ostringstream tmp;
				tmp << "\n[Debug in fnc: " << val << "] ";

				this->braceOperatorImpl(tmp.str());
				return *this;
			}
		};

		template<> class log_base<log_level::internal_error> : public log_base<log_level::normal>
		{
		public:
			log_base(bool saveHistory, bool writeOnExit) :
				log_base<log_level::normal>::log_base{saveHistory, writeOnExit} {}

			template<typename T> log_base &operator()(const T &val)
			{
				console::setColor(console::console_color::red);

				std::ostringstream tmp;
				tmp << "\n[Error #" << val << "] ";

				this->braceOperatorImpl(tmp.str());
				return *this;
			}
		};
	}

	static logger::log_base<logger::log_level::normal> lout{true, true};
	static logger::log_base<logger::log_level::debug> ldbg{false, false};
	static logger::log_base<logger::log_level::internal_error> lerr{true, false};
	#define DBG(x) ldbg(__PRETTY_FUNCTION__) << x
}


#endif // MLK_LOG_LOG_H
