//c++ program
//design by >^.^<
//@date    2019-12-20 23:57:56
#include <iostream>
#include "Jedis.hh"
#include "JError.hh"
#include "JString.hh"

using namespace Jedis;

int main()
{
  Jedis::set("name", "jmx");
  Jedis::get("name");
}
