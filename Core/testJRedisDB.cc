//c++ program
//design by >^.^<
//@date    2019-12-03 04:56:10
#include "JRedisDB.hh"
#include "JString.hh"

#include <memory>

using namespace std;

int main()
{
  JRedisDB db;

  db.SetVal("name", make_shared<JString>("jmx"));
  db.GetVal("name")->Print();
}
