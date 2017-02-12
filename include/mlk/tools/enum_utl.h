//
// Copyright (c) 2013-2017 Christoph Malek
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
		template <typename Enum_Value,
				  typename Enum_Type =
					  typename std::underlying_type<Enum_Value>::type>
		constexpr Enum_Type to_enum_type(Enum_Value enum_member)
		{
			return static_cast<Enum_Type>(enum_member);
		}

		// returns a cast of (enum member) param "enumMember" to an int
		template <typename Int_Type = int, typename Enum_Value>
		constexpr Int_Type to_int(Enum_Value enum_member)
		{
			return static_cast<Int_Type>(enum_member);
		}
	}
}

#endif// MLK_TOOLS_ENUM_UTL_H
