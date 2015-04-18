#pragma once

namespace Utility
{
	template<int... Ns> struct seq { };

	template<int, class> struct seq_builder_helper;
	template<int N, int... Ns> struct seq_builder_helper<N, seq<Ns...>>
	{
		typedef typename seq_builder_helper<N-1, seq<N-1, Ns...>>::type type;
	};
	template<int... Ns> struct seq_builder_helper<0, seq<Ns...>>
	{
		typedef seq<Ns...> type;
	};

	template<int N> struct seq_builder
	{
		typedef typename seq_builder_helper<N, seq<>>::type type;
	};
}
