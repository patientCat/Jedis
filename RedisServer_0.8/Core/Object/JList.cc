//c++ program
//design by >^.^<
//@date    2020-06-24 08:35:56
#include "JList.hh"
#include "../JDatabase.hh"
#include "../JCommand.hh"
#include "../JReply.hh"
#include "../JParams.hh"
#include <assert.h>


using namespace Jedis;
using namespace std;

static bool push(const vector<JString>& params, JReply &reply, int pos);
static JString accordRangeGetList(int start, int end, const JList &);
static JString toString(const JList& j_list, int start, int len);

namespace Jedis{
  JObject JObject::createList()
  {
    JObject obj{};
    obj.setValue(JList{});
    return obj;
  }
}

namespace Jedis{
  bool lpush(const std::vector<Jedis::JString>& params, JReply &reply)
  {
    bool is_ok = push(params, reply, 1);
    return is_ok;
  }

  bool rpush(const std::vector<Jedis::JString>& params, JReply &reply)
  {
    bool is_ok = push(params, reply, -1);
    return is_ok;
  }

  // 获取整个列表
  bool lrange(const std::vector<Jedis::JString>& params, JReply &reply)
  {
    try{
      JObject * obj = G_JDataBase->getObjectByType(params[JPos::JKeyPos], JObject::JDataType::JTypeList);
      if(obj)
      {
        long start, end;
        // get list
        const JList &j_list = std::any_cast<const JList&>(obj->value());
        try {
          start = stol(params[JPos::JParamPos]);
          end = stol(params[JPos::JParamPos + 1]);
          auto str = accordRangeGetList(start, end, j_list);
          reply.setReply(str.data(), str.size());
        }
        catch(std::invalid_argument &x)
        {
          reply.setReply(JReply::JReplyType::Para_Format_Error);
        }

      }else{
        reply.setReply(JReply::JReplyType::Key_Not_Exist) ;
      }
    }
    catch (JError_MismatchType &e) {
      e.error_handler(reply);
    }
    return false;
  }
}

// @Param : pos  1代表从左边插入， -1代表从右边插入
static bool push(const vector<JString>& params, JReply &reply, int pos)
{
  try{
    // 1. key存在， 但类型不对
    // 2. key存在， 类型正确
    // 3. key不存在， 只处理2，3
    JObject* obj = G_JDataBase->getObjectByType(params[JPos::JKeyPos], JObject::JDataType::JTypeList);
    if(!obj)
    {
      // 如果key不存在，就插入一个value
      G_JDataBase->setValue(params[JPos::JKeyPos], JObject::createList(), JObject::JDataType::JTypeList);
    }
    obj = G_JDataBase->getObjectByType(params[JPos::JKeyPos], JObject::JDataType::JTypeList);

    // get list
    JList &j_list = std::any_cast<JList&>(*obj->mutable_value());
    LOG_TRACE << "获取jlist成功";
    for(auto it(params.begin() + 2); it != params.end(); it++)
    {
      if(pos == 1) // 从左边插入
        j_list.emplace_front(std::move(*it));
      else // 从右边插入
        j_list.emplace_back(std::move(*it));
    }

    reply.setReply(JReply::JReplyType::OK);
    return true;

  } catch (JError_MismatchType &e) {
    e.error_handler(reply);
  }
  return false;
}

JString accordRangeGetList(int start, int end, const JList& jlist)
{
  int size = jlist.size();
  if(start < 0)
    throw std::invalid_argument("lrange: start < 0");
  if(end < start || end >= size)
    throw std::invalid_argument("lrange: end is not right");
  return toString(jlist, start, end);
}

JString toString(const JList& j_list, int start, int end)
{
  JString format = "[";
  auto it = j_list.begin();
  int len = end + 1 - start;
  std::advance(it, start);
  while(it != j_list.end() && len--)
  {
    format += *it + ", ";
    it++;
  }
  format += "]";
  return format;
}
