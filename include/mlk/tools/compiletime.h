//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_TOOLS_COMPILETIME_H
#define MLK_TOOLS_COMPILETIME_H


#include <cstdlib>
#include <tuple>


namespace mlk
{
	template<typename T>
	constexpr T get_upper(T t)
	{return t + 1;}

	template<typename T>
	constexpr T get_lower(T t)
	{return t - 1;}

	// get info of a lambda
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
	
	// get index of type 'T' in tuple 'Tuple'
	template<typename T, typename Tuple>
	struct TupleTypeIndex;
	
	template<typename T, typename... Types>
	struct TupleTypeIndex<T, std::tuple<T, Types...>> {
	    static const std::size_t value = 0;
	};
	
	template<typename T, typename U, typename... Types>
	struct TupleTypeIndex<T, std::tuple<U, Types...>> {
	    static const std::size_t value = 1 + TupleTypeIndex<T, std::tuple<Types...>>::value;
	};
}


#endif // MLK_TOOLS_COMPILETIME_H
