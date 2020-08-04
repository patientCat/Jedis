//c++ program
//design by >^.^<
//@date    2020-08-03 01:04:55
#include <iostream>
#include <string_view>
#include <string>
#include <unordered_map>
using namespace std;
// 测试string_view 和 string之间的转换


unordered_map<string, int> hashmap;

// string_view 本身是不持有任何实体的。其本质上就是对字符串的适配器。仅仅持有指针和大小
void get(string_view sv)
{
  cout << hashmap[sv] << endl
}
int main()
{
  hashmap["age"] = 10; 
}
