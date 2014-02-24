//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_FILESYSTEM_FS_BASE_H
#define MLK_FILESYSTEM_FS_BASE_H


#include <string>


namespace mlk
{
	namespace fs
	{
		namespace internal
		{
			class fs_base
			{
			protected:
				std::string m_path;

			public:
				fs_base(const std::string& path) :
					m_path{path}
				{ }

				const std::string& path() const noexcept
				{return m_path;}

				virtual bool exists() const noexcept = 0;
				virtual bool create() const noexcept = 0;
			};
		}
	}
}



#endif // MLK_FILESYSTEM_FS_BASE_H
