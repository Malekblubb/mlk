/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#include <mlk/log/log.h>

#include <sstream>


mlk::logger::LogBase<mlk::logger::LogLevel::Normal>::LogBase(bool saveHistory, bool writeOnExit) :
	m_saveHistory(saveHistory),
	m_writeOnExit(writeOnExit)
{

}

mlk::logger::LogBase<mlk::logger::LogLevel::Normal>::~LogBase()
{
	if(m_writeOnExit)
	{
		// writefun
	}
}

void mlk::logger::LogBase<mlk::logger::LogLevel::Normal>::braceOperatorImpl(const std::string &str)
{
	std::cout << str;

	if(m_saveHistory)
		m_history << str;
}



mlk::logger::LogBase<mlk::logger::LogLevel::Debug>::LogBase(bool saveHistory, bool writeOnExit) :
	mlk::logger::LogBase<mlk::logger::LogLevel::Normal>::LogBase{saveHistory, writeOnExit}
{

}

mlk::logger::LogBase<mlk::logger::LogLevel::InternalError>::LogBase(bool saveHistory, bool writeOnExit) :
	mlk::logger::LogBase<mlk::logger::LogLevel::Normal>::LogBase{saveHistory, writeOnExit}
{

}
