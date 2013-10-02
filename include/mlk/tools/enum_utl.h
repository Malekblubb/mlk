//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_TOOLS_ENUM__H
#define MLK_TOOLS_ENUM__H


#include <type_traits>


namespace mlk
{
	namespace enum_utl
	{
		// returns a casts of (enum member) param "enumMember" to its enum type
		template<typename enum_value, typename enum_type = typename std::underlying_type<enum_value>::type>
		enum_type toEnumType(const enum_value &enumMember)
		{
			return static_cast<enum_type>(enumMember);
		}

		// returns a cast of (enum member) param "enumMember" to an int
		template<typename enum_value> int toInt(const enum_value &enumMember)
		{
			return static_cast<int>(enumMember);
		}
	}
}


#endif // MLK_TOOLS_ENUM__H
