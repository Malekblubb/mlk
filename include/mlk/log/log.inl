//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_LOG_LOG_INL
#define MLK_LOG_LOG_INL


#include "log.h"

#include <mlk/filesystem/fs_handle.h>
#include <mlk/signals_slots/signals_slots.h>


namespace mlk
{
	namespace logger
	{
		inline log_base<mlk::logger::log_level::normal>::log_base(bool save_history, bool write_on_exit, const std::string& save_path) :
			m_save_history{save_history},
			m_write_on_exit{write_on_exit},
			m_save_path{save_path}
		{link_signal(m_entry_added, m_on_entry_added);}

		inline log_base<mlk::logger::log_level::normal>::~log_base()
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

		inline void log_base<mlk::logger::log_level::normal>::entry_added()
		{emit_signal(m_entry_added);}
	}
}


#endif // MLK_LOG_LOG_INL
