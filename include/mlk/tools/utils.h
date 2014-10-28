//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_TOOLS_UTILS_H
#define MLK_TOOLS_UTILS_H


#include <mlk/tools/stl_string_utl.h>

#include <algorithm>
#include <cstdlib>
#include <future>
#include <iostream>
#include <stdexcept>
#include <thread>


namespace mlk
{
	// calls operator<< of 'os' and exits
	// with return EXIT_FAILURE
	template<typename T = std::ostream>
	void exit_with(const std::string& reason, int exit_code = EXIT_FAILURE, T& os = std::cerr)
	{os << reason; std::exit(exit_code);}

	inline bool parse_bool(const std::string& str)
	{
		auto cpy(str);
		stl_string::erase_all(' ', cpy);
		if(cpy.empty())
			throw std::invalid_argument{"cant parse empty string"};

		std::transform(std::begin(cpy), std::end(cpy), std::begin(cpy), [](char c){return std::tolower(c);});
		return cpy[0] == 't' || cpy[0] == '1';
	}

    template<typename Func, typename... Args, typename Lambda_Return = typename mlk::lambda_info<Func>::return_type>
    auto do_async(Func&& f, Args&&... args)
    {
        std::packaged_task<Lambda_Return(Args...)> task{f};
        std::future<Lambda_Return> future{task.get_future()};
        std::thread{std::move(task), std::forward<Args>(args)...}.detach();
        return future;
    }
}


#endif // MLK_TOOLS_UTILS_H
