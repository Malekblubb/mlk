/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef MLK_LOG_LOG_H
#define MLK_LOG_LOG_H


#include <iostream>
#include <sstream>
#include <string>


namespace mlk
{
	namespace logger
	{
		enum class LogLevel : unsigned char
		{
			Normal = 0,
			Debug,
			InternalError
		};


		template<LogLevel Level> class LogBase
		{

		};

		template<> class LogBase<LogLevel::Normal>
		{
		protected:
			bool m_saveHistory, m_writeOnExit;
			std::ostringstream m_history;

		public:
			LogBase() = default;
			LogBase(bool saveHistory, bool writeOnExit);
			~LogBase();

			template<typename T> inline LogBase &operator()(const T &val)
			{
//				Console::resetColor();

				std::ostringstream tmp;
				tmp << "\n[" << val << "] ";

				braceOperatorImpl(tmp.str());

				return *this;
			}

			template<typename T> inline LogBase &operator<<(const T &val)
			{
				std::cout << val;

				if(m_saveHistory)
					m_history << val;

				return *this;
			}

		protected:
			void braceOperatorImpl(const std::string &str);
		};

		template<> class LogBase<LogLevel::Debug> : public LogBase<LogLevel::Normal>
		{
		public:
			LogBase(bool saveHistory, bool writeOnExit);

			template<typename T> inline LogBase &operator()(const T &val)
			{
//				Console::setColor();

				std::ostringstream tmp;
				tmp << "\n[Debug in fnc: " << val << "] ";

				braceOperatorImpl(tmp.str());
				return *this;
			}
		};

		template<> class LogBase<LogLevel::InternalError> : public LogBase<LogLevel::Normal>
		{
		public:
			LogBase(bool saveHistory, bool writeOnExit);

			template<typename T> inline LogBase &operator()(const T &val)
			{
//				Console::setColor();

				std::ostringstream tmp;
				tmp << "\n[Error #" << val << "] ";

				braceOperatorImpl(tmp.str());
				return *this;
			}
		};
	}

	static logger::LogBase<logger::LogLevel::Normal> lout{true, true};
	static logger::LogBase<logger::LogLevel::Debug> ldbg{false, false};
	static logger::LogBase<logger::LogLevel::InternalError> lerr{true, false};
	#define DBG(x) ldbg(__PRETTY_FUNCTION__) << x
}


#endif // MLK_LOG_LOG_H
