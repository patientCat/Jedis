//c++ program
//design by >^.^<
//@date    2019-12-19 04:44:42
#include "JDatabase.hh"
#include "../Base/Logging.hh"
#include "JError.hh"
#include <iostream>
#include <vector>

using namespace Jedis;

// 静态成员变量必须在类外初始化，定义即分配空间
std::once_flag JDataBase::flag1{};
JDataBase *JDataBase::instance{};

using namespace std;

void 
JDataBase::setValue(const JString& key, JObject &&value, JObject::JDataType type)
{
  value.setType(type);
  db_[key] = std::move(value);
  LOG_TRACE << "key = " << key ;
  LOG_TRACE << "db_[key].count = " << db_.count(key);
  
}

bool 
JDataBase::isKeyExist(const JString& key)
{
  LOG_TRACE << "getObjectByType ";
  LOG_TRACE << "key = " << key ;
  return db_.count(key);
}

void 
JDataBase::removeValue(const JString& key)
{
  db_.erase(key);
}



bool
JDataBase::isKeyExist(const Jedis::JString& key, JObject::JDataType type)
{
  return getObjectByType(key, type) != nullptr;
}
JObject *
JDataBase::getObjectByType(const JString& key, JObject::JDataType type)
{
  LOG_TRACE << "getObjectByType ";
  JObject* obj = nullptr;
  if(isKeyExist(key))
  {
    obj = _getObject(key);

    if(obj->type() == JObject::JDataType::JTypeInvalid)
    {
      LOG_SYSFATAL << "DataBase value 没有设置";
    }
    else if(obj->type() != type)
    {
      throw JError_MismatchType{};
    }
  }
  return obj;
}

void
JDataBase::addConnectionInWatchedKeys(const JString& key, const std::shared_ptr<TcpConnection> &conn)
{
  // 针对每一个key，将conn插入。
    watched_keys_[key].insert(conn);
}
