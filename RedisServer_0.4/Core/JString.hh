#ifndef __JSTRING_HH__
#define __JSTRING_HH__

#include <string>

namespace Jedis
{

using JString = std::string;

void set(const char *para1, const char *para2);
void setnx(const char *para1, const char *para2);
void get(const char *para1);
}
#endif
