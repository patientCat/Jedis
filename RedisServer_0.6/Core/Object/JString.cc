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
JObject::createString(const JString& value)
{
  JObject obj(JTypeString);
  obj.setValue(std::move(value));

  return obj;
}


static bool setValue(Jedis::JString key, JString value, bool overlap = false)
{
  if(!overlap)
  {
    if(G_JDataBase->isKeyExist(key) == true)
      return false;
  }
  G_JDataBase->setValue(key, JObject::createString(value), JObject::JDataType::JTypeString);
  return true;
}

// ---------实现set命令-------------
// 这里的参数待定
namespace Jedis{
JError set(const std::vector<Jedis::JString>& paras, ReplyType& reply)
{
  LOG_TRACE << "JString::set";
  auto res = checkKey(paras[JPos::JKeyPos], reply, JObject::JTypeString);
  LOG_TRACE << "after checkKey";
  // 1. key存在，但类型错误, 直接返回
  // 2. key存在，类型正确JError_OK
  // 3. key不存在
  if(res.first == JError_KeyNotExist)
  {
     setValue(paras[JPos::JKeyPos], paras[JPos::JParamPos]);
     LOG_TRACE << "after setValue";
     res.first = JError_OK;
  }
  return res.first;
}

// set string overlap
JError setnx(const std::vector<Jedis::JString>& paras, ReplyType& reply)
{
  // 1. key存在，但类型错误, 直接返回
  // 2. key存在，类型正确JError_OK
  // 3. key不存在
  auto res = checkKey(paras[JPos::JKeyPos], reply, JObject::JTypeString);
  if(res.first == JError_KeyNotExist || res.first == JError_OK)
  {
    setValue(paras[JPos::JKeyPos], paras[JPos::JParamPos], true);
    res.first = JError_OK;
  }
  return res.first;
}

// ---------实现get命令--------------
JError get(const std::vector<Jedis::JString>& paras, ReplyType& reply)
{
  auto res = checkKey(paras[JPos::JKeyPos], reply, JObject::JTypeString);
  // 1. key存在，但类型错误, 直接返回
  // 2. key存在，类型正确JError_OK
  // 3. key不存在
  if(res.first == JError_OK)
  {
    JObject *obj = res.second;
    JString tmp = std::any_cast<JString>(obj->value());
    reply.setReply(tmp.data(), tmp.size());
  }
  return res.first;
}
}

// ---------实现append命令------------
//
