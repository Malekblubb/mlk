//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#include <mlk/filesystem/filesystem.h>


int main()
{
	mlk::fs::fs_handle<mlk::fs::fs_type::file> my_file{"/path/to/file"};
	// shortcut: mlk::fs::file_handle

	if(my_file.exists())
		return 1;

	my_file.create();
	my_file.open_io(std::ios::out);
	my_file.write_line("some line");
	my_file.write("more text in same line");



	mlk::fs::fs_handle<mlk::fs::fs_type::dir> my_dir{"/path/to/dir"};
	// shortcut: mlk::fs::dir_handle

	if(!my_dir.exists())
		my_dir.create();

	// get contents of dir:
	auto content(my_dir.get_content<true>()); // true: recursive or not
	for(auto& a : content) // 'a' is from type 'mlk::fs::dir_item'
		std::cout << a.path << std::endl;
}
