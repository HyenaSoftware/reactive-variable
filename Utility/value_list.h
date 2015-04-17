#pragma once

namespace Utility
{
	/*
		for example:
			typedef value_holder<int, 5> my_compile_time_value;
		
			static const int N = get_value_of<my_compile_time_value>::value;

		
		it's usefule when we want to pass values as types:

		  tuple<value_holder<int, 5>, value_holder<long, 4>> it_stores_values;
	*/

	template<class T, T V> struct value_holder { };

	template<class T> struct get_value_of;
	template<class T, T V> struct get_value_of<value_holder<T, V>>
	{
		static const T value = V;
	};
}
