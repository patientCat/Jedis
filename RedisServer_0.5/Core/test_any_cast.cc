#include "boost/any.hpp"
#include <iostream>
using namespace std;
using namespace boost;

void change(any& x)
{
  int & v = any_cast<int&>(x); 
  v = 100;
}
int main()
{
  any x(10);
  change(x);
  cout << any_cast<int>(x) << endl;
}
