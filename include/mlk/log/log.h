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
			Error
		};


		class LogBase
		{
			std::string m_prefix;
			std::string m_extra;
			std::ostringstream m_stream;

		public:
			~LogBase();

			template<typename T> inline LogBase &operator()(const T &val, const std::string &extra = "")
			{
//				Console::resetColor();

				m_extra = extra;
				m_prefix = val;

				std::cout << this->format();
				return *this;
			}

		private:
			std::string format();
		};


		template<> inline LogBase &LogBase::operator()<LogLevel>(const LogLevel &val, const std::string &extra)
		{
//			Console::resetColor();

			m_extra = extra;

			switch(val)
			{
			case LogLevel::Normal:
				break;
			case LogLevel::Debug:

				m_prefix = "Debug";
//				Console::setColor(WHITE);

				break;
			case LogLevel::Error:

				m_prefix = "Error";
//				Console::setColor(RED);

				break;
			default:
				break;
			}

			std::cout << this->format();
			return *this;
		}

		template<typename T> inline LogBase &operator<<(LogBase &log, const T &val)
		{
			std::cout << val;
			return log;
		}
	}

	static logger::LogBase lout;
	#define DBG(x) lout(mlk::logger::LogLevel::Debug, __PRETTY_FUNCTION__) << x
}


#endif // MLK_LOG_LOG_H
