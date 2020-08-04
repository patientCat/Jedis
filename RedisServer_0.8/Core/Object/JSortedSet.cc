//
// Created by Pawn on 2020/8/3.
//

#include "JSortedSet.hh"
#include "../JCommand.hh"
#include "../JDatabase.hh"
#include "../JParams.hh"
#include "JObject.hh"

using namespace std;

using namespace Jedis;
namespace {
  // 确保key一定存在, 且type正确的时候调用这个函数
  const JSortedSet & get_sorted_set_by_key_unsafe(const JString &key)
  {
    JObject * obj = G_JDataBase->_getObject(key);
    const JSortedSet & x = std::any_cast<const JSortedSet &>(obj->value());
    return x;
  }
  JSortedSet & get_mutable_sorted_set_by_key_unsafe(const JString &key)
  {
    JObject * obj = G_JDataBase->_getObject(key);
    JSortedSet &x = std::any_cast<JSortedSet&>(*obj->mutable_value());
    return x;
  }
}
namespace Jedis{

  JObject JObject::createSortedSet() {
    JObject obj;
    obj.setValue(JSortedSet {});
    return obj;
  }


  bool zadd(const std::vector<Jedis::JString>& params, JReply &reply)
  {
    const JString& key = params[JPos::JKeyPos];
    try{
      bool is_ok = G_JDataBase->isKeyExist(key, JObject::JDataType::JTypeSortedSet);
      if(!is_ok)
      {
        G_JDataBase->setValue(key, JObject::createSortedSet(), JObject::JDataType::JTypeSortedSet) ;
      }

      JSortedSet &sorted_set = get_mutable_sorted_set_by_key_unsafe(key);

      for(int i = JPos::JParamPos; i < params.size(); i+=2)
      {
        double score = std::stod(params[i]);
        sorted_set.insert(score, params[i+1]);
      }

      reply.setReply(JReply::JReplyType::OK);


    } catch (JError_MismatchType &e) {
      e.error_handler(reply) ;
      return false;
    }
    return true;
  }

  // 获得有序集合的成员数
  bool zcard(const std::vector<Jedis::JString>& params, JReply &reply)
  {
    const JString& key = params[JPos::JKeyPos];
    try{
      bool is_ok = G_JDataBase->isKeyExist(key, JObject::JDataType::JTypeSortedSet);
      if(is_ok)
      {
        const JSortedSet &sorted_set = get_sorted_set_by_key_unsafe(key);
        int num =  sorted_set.size();
        reply.setReply(num);
      }else{
        reply.setReply(JReply::JReplyType::Key_Not_Exist);
        return false;
      }
    }
    catch (JError_MismatchType &e) {
      e.error_handler(reply);
      return false;
    }
    return true;
  }

  //  获取指定成员的rank
  bool zrank(const std::vector<Jedis::JString>& params, JReply &reply)
  {
    const JString& key = params[JPos::JKeyPos];
    try{
      bool is_ok = G_JDataBase->isKeyExist(key, JObject::JDataType::JTypeSortedSet);
      if(is_ok)
      {
        const JSortedSet &sorted_set = get_sorted_set_by_key_unsafe(key);
        size_t rank = sorted_set.get_rank(params[JPos::JParamPos]);
        reply.setReply(rank);
      }else{
        reply.setReply(JReply::JReplyType::Key_Not_Exist);
        return false;
      }
    } catch (JError_MismatchType &e) {
      e.error_handler(reply);
      return false;
    }
    return true;
  }


  // 获得指定成员的分值
  bool zscore(const std::vector<Jedis::JString>& params, JReply &reply)
  {  
    const JString& key = params[JPos::JKeyPos];
    try{
      bool is_ok = G_JDataBase->isKeyExist(key, JObject::JDataType::JTypeSortedSet);
      if(is_ok)
      {
        const JSortedSet &sorted_set = get_sorted_set_by_key_unsafe(key);
        double score = sorted_set.get_score(params[JPos::JParamPos]);
        reply.setReply(score);
      }else{
        reply.setReply(JReply::JReplyType::Key_Not_Exist);
        return false;
      }
    } catch (JError_MismatchType &e) {
      e.error_handler(reply);
      return false;
    }
    return true;
  }

  // 获得指定rank = start - end 的成员
  bool zrange(const std::vector<Jedis::JString>& params, JReply &reply)
  {
    if(params.size() > 4)
    {
      reply.setReply(JReply::JReplyType::Params_Num_Error);
      return false;
    }
    bool is_withscore = false;
    if(params.size() == 4){
      JString last_para = params.back();
      std::for_each(last_para.begin(), last_para.end(), [](char &x){
          x = tolower(x);
          });
      if(last_para.compare("withscores") != 0)
      {
        JString info = "withscores spell error";
        reply.setReply(info);
        return false;
      }
      is_withscore = true;
    }

    const JString &key = params[JPos::JKeyPos];
    try{
      bool is_ok = G_JDataBase->isKeyExist(key, JObject::JDataType::JTypeSortedSet);
      if(is_ok)
      {
        const JSortedSet &x = get_sorted_set_by_key_unsafe(key);
        unsigned long start = stoul(params[JPos::JParamPos]);
        unsigned long stop = stoul(params[JPos::JParamPos+1]);

        vector<JString> res = x.zrange( start, stop, is_withscore);
        for(auto & res : res)
        {
          reply.setReply(res);
          reply.setReply("\n", 1);
        }
      }else{
        reply.setReply(JReply::JReplyType::Key_Not_Exist);
        return false;
      }
    } catch (JError_MismatchType &e) {
      e.error_handler(reply);
      return false;
    }
    return true;
  }

} // end namespace jedis
