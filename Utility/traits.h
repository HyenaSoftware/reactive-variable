#pragma once
#include "Macros.h"
#include <type_traits>
#include <tuple>

namespace Utility
{
	struct __has_base__
	{
		typedef char yes;
		typedef int no;
	};

	// SFINAE test
#define define_has_operator(name,OP) \
	template <typename T> struct has_operator_##name : ::Utility::__has_base__ \
	{ \
		template <typename C> static yes test( decltype(&C::operator##OP) ) ; \
		template <typename C> static no test(...); \
		static const bool value = sizeof(test<T>(nullptr)) == sizeof(yes); \
	};

#define DEFINE_HAS_FREE_OPERATOR(name, OP) \
	template <class... As> struct has_free_operator_##name : ::Utility::__has_base__ \
	{ \
		template <class... Bs> static yes test( decltype(operator##OP(std::declval<Bs>()...))* ) ; \
		template <class...> static no test(...); \
		static const bool value = sizeof(test<As...>(nullptr)) == sizeof(yes); \
	};

#define define_has_method(METHOD_NAME) \
	template <typename T> struct has_method_##METHOD_NAME : ::Utility::__has_base__ \
	{ \
	template <typename C> static yes test(decltype(&C::##METHOD_NAME)); \
	template <typename C> static no test(...); \
	static const bool value = sizeof(test<T>(nullptr)) == sizeof(yes); \
	};

#define DEFINE_HAS_FUNCTION(FUNCTION_NAME) \
	template <class... As> struct has_function_##FUNCTION_NAME : ::Utility::__has_base__ \
	{ \
		template <class... Bs> static yes test( decltype(FUNCTION_NAME(std::declval<Bs>()...))* ) ; \
		template <class...> static no test(...); \
		static const bool value = sizeof(test<As...>(nullptr)) == sizeof(yes); \
	};

	define_has_operator(plusplus, ++)
	define_has_operator(post_increment, ++(int))	//???
	define_has_operator(minusminus, --)
	define_has_operator(post_decrement, --(int))	//???
	define_has_operator(less, <)
	define_has_operator(greater, >)
	define_has_operator(less_or_equal, <=)
	define_has_operator(greater_or_equal, >=)
	define_has_operator(negate, !)
	define_has_operator(tilde, ~)
	define_has_operator(dereference, *)
	define_has_operator(call, ())

#define define_has_member(M) \
	template <typename T> struct has_member_##M : ::Utility::__has_base__ \
	{ \
		template <typename C> static yes _test( decltype(&C::##M) ) ; \
		template <typename C> static no _test(...);	\
		static const bool value = sizeof(_test<T>(nullptr)) == sizeof(yes); \
	};

#define define_has_field(F) \
	template <typename T> struct has_field_##F : ::Utility::__has_base__ \
	{ \
		template <typename C> static yes _test( decltype(std::declval<C>().##F)* ) ; \
		template <typename C> static no _test(...);	\
		static const bool value = sizeof(_test<T>(nullptr)) == sizeof(yes); \
	};

#define define_has_typedef(TDEF) \
	template<typename T> struct has_typedef_##TDEF : ::Utility::__has_base__ \
	{ \
		template<typename C> static yes _test(typename C::TDEF*); \
		template<typename C> static no _test(...); \
		static const bool value = sizeof(_test<T>(nullptr)) == sizeof(yes); \
	};

#define define_offset_of(F) \
	template<typename T> struct offset_of \
	{ \
	};

	template<class T, int N> size_t count_of_dims(T(&array)[N])
	{
		return 1 + count_of_dims(array[0]);
	}
	template<class T> size_t count_of_dims(T)
	{
		return 0;
	}

	template<class T, size_t N> size_t size_of_array(T (&) [N])
	{
		return N;
	}

	template<class T, size_t M, size_t N> std::tuple<size_t, size_t> size_of_array2(T (&) [N])
	{
		return std::make_tuple(N,get<>);
	}

	define_has_typedef(value_type);
	define_has_typedef(key_type);
	define_has_typedef(mapped_type);

	template<bool, class T, class = void> struct value_type_of
	{
		typedef typename T::value_type type;
	};
	template<class T, class D> struct value_type_of<false, T, D>
	{
		typedef D type;
	};

	namespace _helper
	{
		struct _invalid_type { };

		template<bool, class T, class = _invalid_type> struct _key_type_of
		{
			typedef typename T::key_type type;
		};
		template<class T, class D> struct _key_type_of<false, T, D>
		{
			typedef D type;
		};

		template<bool, class T, class = _invalid_type> struct _mapped_type_of
		{
			typedef typename T::mapped_type type;
		};
		template<class T, class D> struct _mapped_type_of<false, T, D>
		{
			typedef D type;
		};
	}
	template<class T> struct key_type_of
	{
		typedef typename _helper::_key_type_of<has_typedef_key_type<T>::value, T>::type type;
	};

	template<class T> struct mapped_type_of
	{
		typedef typename _helper::_mapped_type_of<has_typedef_mapped_type<T>::value, T>::type type;
	};

	template<class C> struct is_hash_map
	{
		static const bool value = std::is_same<C, std::hash_map<key_type_of<C>::type, mapped_type_of<C>::type>>::value;
	};

	template<class C> struct is_simple_map
	{
		static const bool value = 
			std::is_same<C, std::map<key_type_of<C>::type, mapped_type_of<C>::type>>::value;
	};

	template<class C> struct is_map
	{
		static const bool value = is_hash_map<C>::value || is_simple_map<C>::value;
	};

	template<class C> struct is_vector
	{
		static const bool value =
			std::conditional<
				has_typedef_value_type<C>::value,
				std::is_same<C, std::vector<value_type_of<has_typedef_value_type<C>::value, C>::type>>,
				false_type
			>::type::value;
	};

	template<class C> struct is_hash_set
	{
		static const bool value =
			std::is_same<C, std::hash_set<typename C::value_type>>::value;
	};

	template<class C> struct is_simple_set
	{
		static const bool value =
			std::is_same<C, set<typename C::value_type>>::value;
	};

	template<class C> struct is_set
	{
		static const bool value =
			is_simple_set<C>::value || is_hash_set<C>::value;
	};

	define_has_typedef(first_type);
	define_has_typedef(second_type);

	template<class C> struct is_pair
	{
		template<class T, bool> struct __helper;
		template<class T> struct __helper<T, true>
		{
			static const bool value = std::is_same<T, std::pair<typename T::first_type, typename T::second_type>>::value;
		};
		template<class T> struct __helper<T, false>
		{
			static const bool value = false;
		};
		static const bool value = __helper<C,
			has_typedef_first_type<C>::value && has_typedef_second_type<C>::value
		>::value;
	};

	define_has_member(begin);
	define_has_member(end);
	define_has_operator(star, *);
	define_has_typedef(iterator);
	define_has_typedef(const_iterator);

	template<class T> struct is_iterator
	{
		static const bool value
			= has_operator_star<T>::value
			&& has_operator_plusplus<T>::value;
	};

	template<class T> struct is_iterable
	{
		static const bool value
			= has_member_begin<T>::value
			&& has_member_end<T>::value
			&& has_typedef_iterator<T>::value
			&& has_typedef_const_iterator<T>::value
		// other requirements...
		;
	};



	/*
		=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		it works for:
			std::function<A(B, Cs...)>	-	STL function wrapper
			A(*)(B, Cs...)				-	pointer to free function
			A(B, Cs...)					-	free function
			A(T::*)(B, Cs...)			-	pointer to member function
			A(T::*)(B, Cs...) const		-	pointer to const member function

		=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

		int func(float, char);


		typedef function_traits<func>::result_type result_type;

			result_type == int


		typedef function_traits<func>::args args;

			args == std::tuple<float, char>

		static const int arity = function_traits<func>::arity;

			arity == 2

		function_traits<func>::arg<0>::type == float

		function_traits<func>::arg<1>::type == char

	*/

	struct undefined;

	template<class... As> struct function_traits_args
	{
		template<int N, class, class... Bs> struct arg_selector
		{
			typedef typename arg_selector<N-1, Bs...>::type type;
		};

		template<class B, class... Bs> struct arg_selector<0, B, Bs...>
		{
			typedef B type;
		};

		template<int N> struct arg
		{
			typedef typename arg_selector<N, As...>::type type;
		};

		typedef std::tuple<As...> args;
		static const int args_arity = sizeof...(As);
	};

	template<class T> struct function_traits;

	template<bool, class T> struct _function_helper_proxy
	{
		typedef function_traits<void> type;
	};

	template<class T> struct _function_helper_proxy<true, T>
	{
		typedef function_traits<decltype(&T::operator())> type;
	};

	template<class T> struct function_traits
		: _function_helper_proxy<has_operator_call<T>::value, T>::type
	{
	};

	template<> struct function_traits<void>
	{
		typedef undefined result_type;
		typedef undefined type;
		static const int args_arity = 0;
	};

	template<class R, class... As> struct function_traits<R (*)(As...)> : function_traits_args<As...>
	{
		typedef R result_type;
		typedef R (*type)(As...);
	};

	template<class R, class... As> struct function_traits<R(As...)> : function_traits_args<As...>
	{
		typedef R result_type;
		typedef R type(As...);
	};

	template<class R, class C, class... As> struct function_traits<R (C::*) (As...)> : function_traits_args<As...>
	{   // non-const specialization
		
		typedef C obj_type;
		typedef R result_type;
		typedef R (C::*type)(As...);
	};

	template<class R, class C, class... As> struct function_traits<R (C::*)(As...) const> : function_traits_args<As...>
	{   // const specialization
		typedef const C obj_type;
		typedef R result_type;
		typedef R (C::*type)(As...);
	};

	template<class F> struct function_traits<std::function<F>> : function_traits<F> { };

	template<class T> struct is_function : std::false_type {};
	template<class R, class... As> struct is_function<R(As...)> : std::true_type { };
	template<class R, class... As> struct is_function<R(*)(As...)> : std::true_type { };
	template<class R, class C, class... As> struct is_function<R(C::*)(As...)> : std::true_type { };
	template<class T> struct is_function<std::function<T>> : std::true_type { };

}
