Reactive variables

Reactive variable is a tiny framework which is created by Visual Studio 2013.

What is it not?
 * it's not multithreaded
 * it doesn't related to http, servers or any network related stuff
 * it doesn't deal with streams


Okay, so what it does?
 * it's useful to create computation graphs
 * ...

Example
```
#include <reactive_framework.h>

using namespace reactive_framework;

void main()
{
  rv<int> a;
  
  rv<int> b = map(a, [](int n_)
  {
     return n_*2;
  }).build();
  
  a = 3;
  
  assert(b == 6);
}
```
