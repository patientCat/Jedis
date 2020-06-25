//c++ program
//design by >^.^<
//@date    2020-06-24 08:35:56
#include "JList.hh"
#include "Jedis.hh"
#include "JCommand.hh"
#include "JReply.hh"
#include <assert.h>


using namespace Jedis;
using namespace std;

static JError push(const vector<JString>& params, ReplyType &reply, int pos);
static JString accordRangeGetList(int start, int end, const JList &);
static JString toString(const JList& j_list, int start, int len);

namespace Jedis{
JObject JObject::createList()
{
  JObject obj(JObject::JTypeList);
  obj.setValue(JList{});
  return obj;
}
}

namespace Jedis{
JError lpush(const std::vector<Jedis::JString>& params, ReplyType &reply)
{
  auto err = push(params, reply, 1);
  return err;
}

JError rpush(const std::vector<Jedis::JString>& params, ReplyType &reply)
{
  auto err = push(params, reply, -1);
  return err;
}

// 获取整个列表
JError lrange(const std::vector<Jedis::JString>& params, ReplyType &reply)
{
  auto res = checkKey(params[JPos::JKeyPos], reply, JObject::JTypeList);
  if(res.first == JError_OK)
  {
    long start, end;
    JObject *obj = res.second;
    // get list
    JList &j_list = boost::any_cast<JList&>(obj->value());
    try{
      start = stol(params[JPos::JParamPos]);
      end = stol(params[JPos::JParamPos + 1]);
      auto str = accordRangeGetList(start, end, j_list);
      ReplyError::setReply(str.data(), str.size(), reply);
    }
    catch(std::invalid_argument &x)
    {
      return JError_InvalidParamFormat;
    }
  }
  return res.first;
}
}

// @Param : pos  1代表从左边插入， -1代表从右边插入
static JError push(const vector<JString>& params, ReplyType &reply, int pos)
{
  auto res = checkKey(params[JPos::JKeyPos], reply, JObject::JTypeList);
  // 1. key存在， 但类型不对
  // 2. key存在， 类型正确
  // 3. key不存在， 只处理2，3
  if(res.first == JError_KeyNotExist)
  {
    // create list
    G_JDataBase->setValue(params[JPos::JKeyPos], JObject::createList(), JObject::JDataType::JTypeList);
    res.first = JError_OK;
  }
  if(res.first == JError_OK)
  {
    LOG_TRACE << "开始插入";
    JObject *obj = NULL;
    G_JDataBase->getValueByType(params[JPos::JKeyPos], obj, JObject::JDataType::JTypeList);

    // get list
    JList &j_list = boost::any_cast<JList&>(obj->value());
    LOG_TRACE << "获取jlist成功";
    for(auto it(params.begin() + 2); it != params.end(); it++)
    {
      if(pos == 1) // 从左边插入
      j_list.emplace_front(std::move(*it)); 
      else // 从右边插入 
      j_list.emplace_back(std::move(*it)); 
    }
  }
  return res.first;
}

JString accordRangeGetList(int start, int end, const JList& jlist)
{
  int size = jlist.size();
  start = start >= 0 ? start : size + start;
  end = end >= 0 ? end : size + end;
  // 返回空链表
  if(start >= size || end >= size || end < start)
    return {};

  assert(start <= end && end < size);
  return toString(jlist, start, end); 
}

JString toString(const JList& j_list, int start, int end)
{
  JString format = "[";
  auto it = j_list.begin();
  int len = end + 1 - start;
  while(start--)
  {
    it++;
  }
  while(it != j_list.end() && len--)
  {
    format += *it + ", ";
    it++;
  }
  format += "]";
  return format;
}
