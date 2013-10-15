//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_CONTAINERS_MIXED_CONTAINER_TYPE_H
#define MLK_CONTAINERS_MIXED_CONTAINER_TYPE_H


namespace mlk
{
	namespace cnt
	{
		class mixed_container;

		namespace internal
		{
			class mixed_cnt_type_base
			{
			public:
				mixed_cnt_type_base() = default;
				virtual ~mixed_cnt_type_base() = default;
			};


			template<typename T>
			class mixed_cnt_type : public mixed_cnt_type_base
			{
				T m_var;
				using type = T;

				friend class cnt::mixed_container;

			public:
				mixed_cnt_type(const T& val) :
					m_var{val}
				{ }

				~mixed_cnt_type() = default;

				mixed_cnt_type(const mixed_cnt_type& o) :
					m_var{o.m_var}
				{ }

				mixed_cnt_type(mixed_cnt_type&& o) noexcept :
					m_var{std::move(o.m_var)}
				{ }

				mixed_cnt_type& operator=(const mixed_cnt_type& o) noexcept(noexcept(o.operator=)) // is this used like this ?
				{
					m_var = o.m_var;
					return *this;
				}

				mixed_cnt_type& operator=(mixed_cnt_type&& o) noexcept(noexcept(o.operator=))
				{
					m_var = std::move(o.m_var);
					return *this;
				}
			};
		}
	}
}


#endif // MLK_CONTAINERS_MIXED_CONTAINER_TYPE_H
