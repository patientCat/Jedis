//c++ program
//design by >^.^<
//@date    2019-12-19 05:02:17
#include "JString.hh"
#include "../JDatabase.hh"
#include "../JCommand.hh"
#include "../JCast.hh"
#include "../JReply.hh"
#include "../JParams.hh"
#include <string_view>
#include <iostream>

// 就打算实现三个命令，
// set，get，append

using namespace Jedis;

JObject
JObject::createString()
{
  JObject obj{};
  obj.setValue(JString{});

  return obj;
}


static bool setValue(Jedis::JString key, JString value, bool overlap = false)
{
  if(!overlap)
  {
    if(G_JDataBase->isKeyExist(key) == true)
      return false;
  }
  JObject x = JObject::createString();
  x.setValue(value);
  G_JDataBase->setValue(key, std::move(x), JObject::JDataType::JTypeString);
  return true;
}

// ---------实现set命令-------------
// 这里的参数待定
namespace Jedis{
bool set(const std::vector<Jedis::JString>& paras, JReply & reply)
{
  LOG_TRACE << "JString::set";
  try{
    const JString & key = paras[JPos::JKeyPos];
    bool is_ok = G_JDataBase->isKeyExist(key, JObject::JDataType::JTypeString);
    if(!is_ok){
      // key 不存在
      setValue(paras[JPos::JKeyPos], paras[JPos::JParamPos], false);
      reply.setReply(JReply::JReplyType::OK);
      return true;
    }else{
      reply.setReply(JReply::JReplyType::Key_Already_Exist);
      return false;
    }
  } catch (JError &e) {
    e.error_handler(reply);
  }
  return false;
}

// set string overlap
bool setnx(const std::vector<Jedis::JString>& paras, JReply & reply)
{
  // 1. key存在，但类型错误, 直接返回
  // 2. key存在，类型正确JError_OK
  // 3. key不存在
  try{ // JError_KeyNotExist
    const JString & key = paras[JPos::JKeyPos];
    bool is_ok = G_JDataBase->isKeyExist(key, JObject::JDataType::JTypeString);
    setValue(paras[JPos::JKeyPos], paras[JPos::JParamPos], true);
    reply.setReply(JReply::JReplyType::OK);
    return true;
  } catch (JError_MismatchType &e) {
    e.error_handler(reply);
  }
  return false;
}

// ---------实现get命令--------------
bool get(const std::vector<Jedis::JString>& paras, JReply & reply)
{
  try{
    JObject* obj = G_JDataBase->getObjectByType(paras[JPos::JKeyPos], JObject::JDataType::JTypeString);
    if(obj)
    {
      const JString &str = std::any_cast<JString>(obj->value());
      reply.setReply(str);
      return true;
    }else{
      reply.setReply(JReply::JReplyType::Key_Not_Exist);
      return false;
    }
  } catch (JError_MismatchType &e) {
    e.error_handler(reply);
  }
  return false;
}
} // end namespace Jedis

// ---------实现append命令------------
//
