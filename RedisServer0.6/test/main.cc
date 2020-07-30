//c++ program
//design by >^.^<
//@date    2020-07-30 06:27:29
#include <iostream>

#include "test/test.h"
#include <unordered_map>

using namespace std;
int main()
{
  unordered_map<int, int> hashmap;
  hashmap.insert(1, 10);
  auto iter = hashmap.find(1);
  TEST::test(10);
}
