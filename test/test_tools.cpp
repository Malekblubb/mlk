//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//


#include <mlk/tools/tools.h>

#include <iostream>


int main()
{
	// enum (class) tools
	enum class my_enum_class : char {en1, en2, en3};
	std::cout << mlk::enum_utl::to_int(my_enum_class::en3) << std::endl; // cast to int; prints 2

	auto underlaying_type(mlk::enum_utl::to_enum_type(my_enum_class::en1)); // automatic cast to underlaying type(char)
	std::cout << static_cast<int>(underlaying_type) << std::endl; // prints 0



	std::cout << "\n########################\n\n";



	// random tools
	int random_number{mlk::rnd(0, 999)};
	std::cout << random_number << std::endl; // prints a random number between [0 and 999]



	std::cout << "\n########################\n\n";



	// std::string tools
	int some_int{15};
	std::string to_str{mlk::stl_string::to_string(some_int)}; // to string
	int to_int(mlk::stl_string::to_int(to_str)); // to int
	std::cout << mlk::stl_string::to_hex_int(to_str) << std::endl; // to hex int; prints 21

	std::string numeric_str{"123456789"};
	std::cout << mlk::stl_string::is_numeric(numeric_str) << std::endl; // prints 1

	std::string count_str{"___aaa___b_bcccc_c---"};
	std::cout << mlk::stl_string::count_of('c', count_str) << std::endl; // prints 5
	mlk::stl_string::erase_all('b', count_str); // erase all 'b'
	std::cout << count_str << std::endl; // prints ___aaa____cccc_c---
	mlk::stl_string::erase_first('_', count_str); // erase first '_'
	std::cout << count_str << std::endl; // prints __aaa____cccc_c---
	mlk::stl_string::erase_last('_', count_str); // erase last '_'
	std::cout << count_str << std::endl; // prints __aaa____ccccc---



	std::cout << "\n########################\n\n";



	// type tools
	std::cout << mlk::type_utl::is_str_or_int<int>() << std::endl; // prints 1; type 'int' is integral
	std::cout << mlk::type_utl::is_str_or_int<float>() << std::endl; // prints 0; type 'float' is not integral

	std::cout << mlk::type_utl::is_str<const char*>() << std::endl; // prints 1; type 'const char*' is a string
	std::cout << mlk::type_utl::is_str<const char>() << std::endl; // prints 0; type 'const char' is not a string
	std::cout << mlk::type_utl::is_str<std::string>() << std::endl; // prints 1; type 'std::string' is a string
}
