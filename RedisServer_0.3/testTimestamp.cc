//c++ program
//design by >^.^<
//@date    2019-12-06 06:19:46
#include <iostream>
#include "Timestamp.hh"
#include <chrono>

using namespace std;

int main()
{
  Timestamp ts;
  Timestamp ts2(std::chrono::milliseconds(200));
  ts += ts2;
  cout << ts.Milliseconds().count() << endl;
}
