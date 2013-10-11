//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_CONTAINERS_ERROR_TYPE_H
#define MLK_CONTAINERS_ERROR_TYPE_H


#include <functional>
#include <string>
#include <type_traits>


namespace mlk
{
	namespace cnt
	{
		class error_type_base
		{
			std::string m_msg;
			std::function<void()> m_on_called;

		public:
			error_type_base(const std::string& msg, const std::function<void()>& on_called) :
				m_msg{msg},
				m_on_called{on_called}
			{ }

			virtual ~error_type_base() = default;

			void call()
			{
				m_on_called();
			}

			std::string msg() const noexcept {return m_msg;}
		};

		template<typename T>
		class error_type : public error_type_base
		{
			typename std::enable_if<std::is_enum<T>::value ||
									std::is_integral<T>::value, T>::type m_code;

		public:
			error_type(const T& code, const std::string& msg, const std::function<void()>& on_called) :
				error_type_base{msg, on_called},
				m_code{code}
			{ }

			~error_type() = default;

			bool cmp_code(const T& other_code)
			{
				return m_code == other_code;
			}
		};
	}
}



#endif // MLK_CONTAINERS_ERROR_CONTAINER_H
