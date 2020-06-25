#ifndef __JERROR_HH__
#define __JERROR_HH__

#include <iostream>
enum JError
{
  JError_OK = 0,
  JError_InvalidType,
  JError_KeyNotExist,
  JError_MismatchType
}; 

template <typename T>
void print(T t, std::string str= "")
{
  using namespace std;
  cout << str << endl;
  cout << t << endl;
}
#endif
