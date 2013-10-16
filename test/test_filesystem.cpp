//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#include <mlk/filesystem/filesystem.h>


int main()
{
	mlk::fs::fs_handle<mlk::fs::fs_type::file> my_file{"/path/to/file"};

	if(my_file.exists())
		return 1;

	my_file.create();
	my_file.open_io(std::ios::out);
	my_file.write_line("some line");
	my_file.write("more text in same line");



	mlk::fs::fs_handle<mlk::fs::fs_type::dir> my_dir{"/path/to/dir"};

	if(!my_dir.exists())
		my_dir.create();
}
