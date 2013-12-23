//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_TOOLS_ENUM_UTL_H
#define MLK_TOOLS_ENUM_UTL_H


#include <type_traits>


namespace mlk
{
	namespace enum_utl
	{
		// returns a casts of (enum member) param "enumMember" to its enum type
		template<typename enum_value, typename enum_type = typename std::underlying_type<enum_value>::type>
		constexpr enum_type to_enum_type(const enum_value &enum_member)
		{return static_cast<enum_type>(enum_member);}

		// returns a cast of (enum member) param "enumMember" to an int
		template<typename enum_value>
		constexpr int to_int(const enum_value &enum_member)
		{return static_cast<int>(enum_member);}
	}
}


#endif // MLK_TOOLS_ENUM_UTL_H
