//
// Copyright (c) 2013-2017 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_CONTAINERS_ERROR_TYPE_H
#define MLK_CONTAINERS_ERROR_TYPE_H

#include <mlk/signals_slots/slot.h>

#include <string>
#include <type_traits>

namespace mlk
{
	namespace cnt
	{
		namespace internal
		{
			class error_type_base
			{
				std::string m_msg;
				slot<> m_on_called;

			public:
				error_type_base(const std::string& msg,
								const slot<>& on_called) noexcept
					: m_msg{msg}, m_on_called{on_called}
				{
				}

				virtual ~error_type_base() = default;

				void call() { m_on_called(); }

				const std::string& msg() const noexcept { return m_msg; }
			};
		}

		template <typename T>
		class error_type : public internal::error_type_base
		{
			typename std::enable_if<std::is_enum<T>() || std::is_integral<T>(),
									T>::type m_code;

		public:
			error_type(const T& code, const std::string& msg,
					   const slot<>& on_called = {[] {}}) noexcept
				: error_type_base{msg, on_called}, m_code{code}
			{
			}

			~error_type() = default;

			bool cmp_code(const T& other_code) const noexcept
			{
				return m_code == other_code;
			}
		};
	}
}

#endif// MLK_CONTAINERS_ERROR_CONTAINER_H
