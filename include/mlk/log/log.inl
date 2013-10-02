//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_LOG_LOG_INL
#define MLK_LOG_LOG_INL


#include "log.h"

#include <mlk/filesystem/filesystem.h>


mlk::logger::log_base<mlk::logger::log_level::normal>::~log_base()
{
	console::resetColor();

	if(m_writeOnExit && (!m_history.str().empty()))
	{
		fs::fs_handle<fs::fs_type::file> file{m_savePath};
		file.openIo(std::ios::out | std::ios::trunc);
		file.write(m_history.str());
	}
}


#endif // MLK_LOG_LOG_INL
