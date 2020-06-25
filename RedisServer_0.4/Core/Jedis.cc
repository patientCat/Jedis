//c++ program
//design by >^.^<
//@date    2019-12-19 04:44:42
#include "Jedis.hh"
#include <iostream>

using namespace Jedis;

// 静态成员变量必须在类外初始化，定义即分配空间
std::once_flag JDataBase::flag1{};
JDataBase *JDataBase::instance{};

void 
JDataBase::setValue(std::string_view key, JObject &&value)
{
  db_[key] = std::move(value);
}

bool 
JDataBase::isKeyExist(std::string_view key)
{
  return db_.count(key);
}

void 
JDataBase::removeValue(std::string_view key)
{
  db_.erase(key);
}

JError
JDataBase::getValueByType(std::string_view key, JObject *&value, JObject::JDataType type)
{
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
