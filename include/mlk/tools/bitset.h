//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_TOOLS_BITSET_H
#define MLK_TOOLS_BITSET_H


#include "enum_utl.h"

#include <bitset>


namespace mlk
{
	// std::bitset wrapper
	// that can be used with enum classes
	template<typename T, std::size_t size>
	class bitset
	{
		std::bitset<size> m_bitset;

	public:
		bitset() = default;

		void operator|=(T value)
		{m_bitset[enum_utl::to_int<std::size_t>(value)] = true;}

		auto operator[](T test_value)
		-> decltype(m_bitset[enum_utl::to_int<std::size_t>(test_value)])
		{return m_bitset[enum_utl::to_int<std::size_t>(test_value)];}

		bool operator&(T test_value) const
		{return m_bitset[enum_utl::to_int<std::size_t>(test_value)] == true;}

		void remove(T value)
		{m_bitset[enum_utl::to_int<std::size_t>(value)] = false;}
	};
}


#endif // MLK_TOOLS_BITSET_H
