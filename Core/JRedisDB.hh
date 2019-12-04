#ifndef __JREDIS_HH__
#define __JREDIS_HH__

#include "JObject.hh"
#include <unordered_map>


class JRedisDB
{
public:
  JRedisDB() = default;
  void SetVal(const std::string& key, JObjectPtr value);
  JObjectPtr GetVal(const std::string& key);
private:
  std::unordered_map<std::string, JObjectPtr> dict_;
};
#endif
