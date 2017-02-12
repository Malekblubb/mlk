//
// Copyright (c) 2013-2017 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_TOOLS_BITSET_H
#define MLK_TOOLS_BITSET_H

#include "enum_utl.h"
#include "type_utl.h"

#include <bitset>
#include <type_traits>

namespace mlk
{
	// std::bitset wrapper
	// that can be used with enum classes
	template <typename T, std::size_t size>
	class bitset
	{
		std::bitset<size> m_bitset;

	public:
		using type = T;

		bitset() = default;

		void operator|=(type value)
		{
			m_bitset[enum_utl::to_int<std::size_t>(value)] = true;
		}

		auto operator[](type test_value)
			-> decltype(m_bitset[enum_utl::to_int<std::size_t>(test_value)])
		{
			return m_bitset[enum_utl::to_int<std::size_t>(test_value)];
		}

		bool operator&(type test_value) const
		{
			return m_bitset[enum_utl::to_int<std::size_t>(test_value)] == true;
		}

		void toggle(type value)
		{
			m_bitset.flip(enum_utl::to_int<std::size_t>(value));
		}

		void remove(type value)
		{
			m_bitset[enum_utl::to_int<std::size_t>(value)] = false;
		}

		void remove_all() noexcept { m_bitset.reset(); }

		bool is_empty() const noexcept { return m_bitset.none(); }

		template <typename Ret_Type>
		Ret_Type get_as() const noexcept
		{
			return type_utl::to_type<Ret_Type>(m_bitset);
		}
	};

	// bitset for enum class type and enum class member-size (e.g.:
	// my_enum::num)
	template <typename T,
			  typename std::enable_if<std::is_enum<T>::value, T>::type size>
	class ebitset : public bitset<T, enum_utl::to_int<std::size_t>(size)>
	{
	};
}

#endif// MLK_TOOLS_BITSET_H
