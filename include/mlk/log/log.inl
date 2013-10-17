//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_LOG_LOG_INL
#define MLK_LOG_LOG_INL


#include "log.h"

#include <mlk/filesystem/filesystem.h>


inline mlk::logger::log_base<mlk::logger::log_level::normal>::~log_base()
{
	console::reset_color();

	if(m_write_on_exit && (!m_history.str().empty()))
	{
		if(!m_save_path.empty())
		{
			fs::fs_handle<fs::fs_type::file> file{m_save_path};
			file.open_io(std::ios::out | std::ios::trunc);
			file.write(m_history.str());
		}
	}
}


#endif // MLK_LOG_LOG_INL
