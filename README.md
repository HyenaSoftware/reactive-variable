Reactive variables

Reactive variable is a tiny framework which is created by Visual Studio 2013.

What is it not?
 * it's not multithreaded
 * it's not event based
 * it doesn't related to http, servers or any network related stuff
 * it doesn't deal with streams

Okay, so what it does?
 * it's useful to create computation graphs
 * ...

Example
~~~cpp

#include <reactive_framework.h>

using namespace reactive_framework;

void how_map_works()
{
  rv<int> a;
  
  rv<int> b = map(a, [](int n_)
  {
     return n_*2;
  }).build();
  
  a = 3;
  
  assert(b == 6);
}

void how_join_works()
{
  rv<int> a;
  rv<float> b;
  rv<char> c;
  
  rv<std::tuple<int, float, char>> d;
  
  join(a, b, c).to(d);
  
  a = 3;
  b = 5.f;
  c = 'x';
  
  const auto expected_result = std::make_tuple(3, 5.f, 'x');
  
  assert(expected_result == d);
}

void how_merge_works()
{
  rv<int> a, b, c;
  rv<std::vector<int>> d;
  
  merge(a, b, c).to(d);
  
  a = 1;
  b = 2;
  c = 3;
  
  const std::vector<int> expected_result { 1, 2, 3 };
  
  assert(expected_result == d);
}

void how_flatmap_works()
{
  rv<std::vector<std::vector<int>>> a;
  rv<std::vector<int>> b;
  
  const std::vector<std::vector<int>> test_value
	{
		{ 1, 2, 3 },
		{ 4, 5},
		{ 6 }
	};
	
	a = test_value;
	
	flatmap(a).to(b);
	
	const std::vector<int> expected_value { 1, 2, 3, 4, 5, 6 };
	
	assert(expected_value == b);
}
~~~
