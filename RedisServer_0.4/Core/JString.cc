//c++ program
//design by >^.^<
//@date    2019-12-19 05:02:17
#include "Jedis.hh"
#include "JString.hh"
#include <string_view>
#include <iostream>

// 就打算实现三个命令，
// set，get，append

namespace Jedis{

JObject
JObject::createString(const JString& value)
{
  JObject obj(JTypeString);
  obj.setValue(value);

  return obj;
}


static bool setValue(std::string_view key, JString value, bool overlap = false)
{
  if(!overlap)
  {
    if(G_JDataBase->isKeyExist(key) == true)
      return false;
  }
  G_JDataBase->setValue(key, JObject::createString(value));
  return true;
}

// ---------实现set命令-------------
// 这里的参数待定
void set(const char *para1, const char *para2)
{
  bool isOK = setValue(para1, para2);
  assert(isOK);
}

// set string overlap
void setnx(const char *para1, const char *para2)
{
  bool isOK = setValue(para1, para2, true);
}

// ---------实现get命令--------------
void get(const char *para1)
{
  JObject *obj;
  JError err =  G_JDataBase->getValueByType(para1, obj, JObject::JTypeString);
  if (err != JError_OK)
  {
    // replyError();
    return;
  }
  // 输出
  JString tmp = any_cast<JString>(obj->value());
  std::cout << tmp << std::endl;
  return;
}

// ---------实现append命令------------
//
}
