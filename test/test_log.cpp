//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#include <mlk/containers/error_container.h>
#include <mlk/log/log.h>

#include <iostream>


void fnc_that_throws()
{
	throw;
}

int main()
{
	mlk::lout("Log \"title\"") << "some string"; // prints: [Log "title"] some string
	mlk::lerr() << "some error string " << 5.5 << " test"; // prints: [Error] some error string 5.5 test; in red color
	mlk::lerr()["my function?"] << "more error text"; // prints: [Error] [my function?] more error text; in red color
	MLK_DBG("debug message"); // prints: [Debug in fnc: int main()] debug message; in white color


	// use with error_container
	enum my_errors : int
	{
		error1 = 0,
		error2,
		error3
		// ...
	};

	
	// easy link while runtime
	mlk::lerr_i().link_error(error2, "msg", {[]{std::cout << "my nice lambda" << std::endl;}});
	
	
	// set new error_container (will override old "links")
	mlk::cnt::error_container my_error_cnt;
	my_error_cnt.link(error1,
					  "some custom error msg",
					  {[]{std::cout << "my extra function" << std::endl;}}); // links parameter "msg" and "fnc" to error1
	my_error_cnt.link(error3, "", {&fnc_that_throws});


	mlk::lerr_i().set_error_container(my_error_cnt); // need to set the container
	mlk::lerr(error1) << "more error msg"; // invokes previously linked error1 function
	mlk::lerr(error3); // invokes previously linked error3 function


	// output:
	// [Error #0] some custom error msg my extra function
	// more error msg
	// [Error #2]  terminate called without an active exception
}
