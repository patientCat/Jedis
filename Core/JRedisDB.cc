//c++ program
//design by >^.^<
//@date    2019-12-03 04:19:41
#include "JRedisDB.hh"
#include "JObject.hh"

using std::string;

void
JRedisDB::SetVal(const string& key, JObjectPtr value)
{
  dict_[key] = value;
}

JObjectPtr
JRedisDB::GetVal(const string& key)
{
  return dict_[key];
}

