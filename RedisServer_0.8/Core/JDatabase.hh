#ifndef __JEDIS_HH__
#define __JEDIS_HH__

// #include <string_view>

#include <cassert>
#include "./Object/JString.hh"
#include "./Object/JObject.hh"

#include <string_view>
#include <unordered_map>
#include <mutex>
#include <functional>
#include <memory>
#include <set>

#include <any>
#include "../Base/Noncopyable.hh"


class TcpConnection;
namespace  Jedis{


class JObject;  



class JDataBase
: Noncopyable
{
public:
  static JDataBase* getInstance()
  {
    std::call_once(flag1, std::bind(&JDataBase::init));
    return instance;
  }


  void setValue(const Jedis::JString& key, JObject &&value, JObject::JDataType type);
  // void setValue(const Jedis::JString& key, JObject &&value);

  JObject* getObjectByType(const Jedis::JString&, JObject::JDataType type);
  bool isKeyExist(const Jedis::JString& key, JObject::JDataType type);
  bool isKeyExist(const Jedis::JString& key);
  void removeValue(const Jedis::JString& key);

  using TcpConnectionSet = std::set<std::shared_ptr<TcpConnection>>;
  using WatchedKeyMap = std::unordered_map<Jedis::JString, TcpConnectionSet>;

  void addConnectionInWatchedKeys(const JString& key, const std::shared_ptr<TcpConnection> &conn);
  TcpConnectionSet *getConnectionSetOf(const JString& key)
  {
    if(!watched_keys_.count(key))
      return nullptr;
    else
      return &watched_keys_[key];
  }
  // 不安全的
  JObject *_getObject(const Jedis::JString& key)
  {
    assert(isKeyExist(key));
    return &db_[key];
  }
private:

  static void init() { instance = new JDataBase(); }

  JDataBase() = default;

private:
  std::unordered_map<Jedis::JString, JObject> db_;
  // 表示每个key被哪些客户端监视
  WatchedKeyMap watched_keys_;

  static std::once_flag flag1;
  static JDataBase *instance;
};


#define G_JDataBase JDataBase::getInstance()

}
#endif

