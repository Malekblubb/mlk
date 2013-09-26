#include <mlk/log/log.h>

#include <sstream>


mlk::logger::LogBase::~LogBase()
{
	std::cout << "\n";
}

std::string mlk::logger::LogBase::format()
{
	m_stream.flush();

	m_stream << std::endl; // begin on a new line when "()" is called
	m_stream << "[" << m_prefix << "]";

	if((m_extra.empty()) || (m_extra == ""))
		m_stream << " ";
	else
		m_stream << "(" << m_extra << ") ";

	return m_stream.str();
}
