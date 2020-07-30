#ifndef __JEDIS_HH__
#define __JEDIS_HH__

// #include <string_view>
#include "./Object/JObject.hh"
#include "./Object/JString.hh"
#include "JError.hh"

#include <cassert>

#include <string_view>
#include <unordered_map>
#include <mutex>
#include <functional>

#include <boost/any.hpp>
#include <boost/noncopyable.hpp>


namespace  Jedis{



inline void swap(JObject &lhs, JObject &rhs)
{
  lhs.swap(rhs);
}

class JDataBase
: boost::noncopyable
{
public:
  static JDataBase* getInstance()
  {
    std::call_once(flag1, std::bind(&JDataBase::init));
    return instance;
  }


  void setValue(const Jedis::JString& key, JObject &&value, JObject::JDataType type);
  // void setValue(const Jedis::JString& key, JObject &&value);

  JError getValueByType(const Jedis::JString&, JObject *&value, JObject::JDataType type);
  bool isKeyExist(const Jedis::JString& key);
  void removeValue(const Jedis::JString& key);

private:
  JObject *_getObject(const Jedis::JString& key)
  {
    assert(isKeyExist(key));
    return &db_[key];
  }

  static void init() { instance = new JDataBase(); }

  JDataBase() = default;

private:
  std::unordered_map<Jedis::JString, JObject> db_;
  static std::once_flag flag1;
  static JDataBase *instance;
};


#define G_JDataBase JDataBase::getInstance()

}
#endif

