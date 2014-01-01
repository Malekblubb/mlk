//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_LOG_LOG_INL
#define MLK_LOG_LOG_INL


#include "log_impl.h"

#include <mlk/filesystem/filesystem.h>
#include <mlk/signals_slots/signals_slots.h>


namespace mlk
{
	namespace logger
	{
		inline log_base<mlk::logger::log_level::normal>::log_base(bool save_history, bool write_on_exit, bool override_old_log, const std::string& save_path) :
			m_save_history{save_history},
			m_write_on_exit{write_on_exit},
			m_save_path{save_path},
			m_mode{override_old_log ? m_mode = std::ios::out | std::ios::trunc : m_mode = std::ios::out | std::ios::app}
		{ }

		inline log_base<mlk::logger::log_level::normal>::~log_base()
		{
			console::reset_color();

			if(m_write_on_exit && (!m_history.str().empty()))
			{
				if(!m_save_path.empty())
				{
					fs::fs_handle<fs::fs_type::file> file{m_save_path};
					file.open_io(m_mode);
					file.write(m_history.str());
				}
			}

			std::cout << std::endl;
		}

		inline void log_base<mlk::logger::log_level::normal>::entry_added(const std::string& last_entry)
		{emit_signal<void>(m_entry_added, last_entry);}
	}
}


#endif // MLK_LOG_LOG_INL
