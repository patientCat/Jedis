//c++ program
//design by >^.^<
//@date    2019-12-19 04:44:42
#include "Jedis.hh"
#include "../Base/Logging.hh"
#include <iostream>

using namespace Jedis;

// 静态成员变量必须在类外初始化，定义即分配空间
std::once_flag JDataBase::flag1{};
JDataBase *JDataBase::instance{};

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
  LOG_TRACE << "getValueByType ";
  LOG_TRACE << "key = " << key ;
  return db_.count(key);
}

void 
JDataBase::removeValue(const JString& key)
{
  db_.erase(key);
}

JError
JDataBase::getValueByType(const JString& key, JObject *&value, JObject::JDataType type)
{
  LOG_TRACE << "getValueByType ";
  if(isKeyExist(key))
  {
    value = _getObject(key);

    if(value->type() == JObject::JTypeInvalid)
    {
      return JError_InvalidType;
    }
    else if(value->type() == type)
    {
      return JError_OK;
    }
    else{
      return JError_MismatchType;
    }
  }
  else{
    return JError::JError_KeyNotExist;
  }
}
