//
// Copyright (c) 2013-2017 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_FILESYSTEM_FS_UTL_H
#define MLK_FILESYSTEM_FS_UTL_H

#include <mlk/filesystem/fs_handle.h>
#include <mlk/tools/type_utl.h>

#include <string>

namespace mlk
{
	namespace fs
	{
		template <typename T>
		std::string as_path(const T& t)
		{
			static_assert(type_utl::is_str<T>(), "string required");
			return t;
		}

		template <>
		inline std::string as_path<fs_handle<fs_type::file>>(
			const fs_handle<fs_type::file>& file)
		{
			return file.path();
		}
	}
}

#endif// MLK_FILESYSTEM_FS_UTL_H
