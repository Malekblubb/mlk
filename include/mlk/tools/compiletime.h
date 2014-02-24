//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_TOOLS_COMPILETIME_H
#define MLK_TOOLS_COMPILETIME_H


#include <tuple>


namespace mlk
{
	template<typename T>
	constexpr T get_upper(T t)
	{return t + 1;}

	template<typename T>
	constexpr T get_lower(T t)
	{return t - 1;}

	template<typename Lambda>
	struct lambda_info : public lambda_info<decltype(&Lambda::operator())>
	{ };

	template <typename Class, typename Return_Type, typename... Lambda_Args>
	class lambda_info<Return_Type(Class::*)(Lambda_Args...) const>
	{
		using helper_tup = std::tuple<Lambda_Args...>;

	public:
		// return type
		using return_type = Return_Type;

		// argument type(s)
		template<std::size_t arg_index>
		struct argument
		{
			static_assert(arg_index < std::tuple_size<helper_tup>::value, "lambda_info: invalid argument index");
			using type = typename std::tuple_element<arg_index, helper_tup>::type;
		};
	};
}


#endif // MLK_TOOLS_COMPILETIME_H
