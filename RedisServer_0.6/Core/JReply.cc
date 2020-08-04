//c++ program
//design by >^.^<
//@date    2020-06-24 08:51:20
#include "JReply.hh"
#include "JDatabase.hh"
#include "../Base/Logging.hh"


using namespace Jedis;


const Jedis::JString ReplyType::kErrMismatchTypeStr{"类型不匹配"};
const Jedis::JString ReplyType::kErrKeyNotExistStr{"key不存在"};
const Jedis::JString ReplyType::kErrInvalidType{"无效的类型，代码错误"};
const Jedis::JString ReplyType::kErrParams{"参数数量错误"};
const Jedis::JString ReplyType::kErrCmdNotExist{"命令不存在"};
const Jedis::JString ReplyType::kErrInvalidParamFormat{"参数格式错误"};
const Jedis::JString ReplyType::kErrOk{"OK"};
const Jedis::JString ReplyType::kJianTou{"--->"};

namespace Jedis{
std::pair<JError, JObject*> checkKey(const JString& para, ReplyType& reply, JObject::JDataType objType)
{
  JObject *obj = NULL;
  JError err =  G_JDataBase->getValueByType(para, obj, objType);
  if (err != JError_OK)
  {
    //  键存在，但类型错误
    if(err == JError_MismatchType)
    {
      return {err, NULL};
    }
    if(err == JError_KeyNotExist)
    {
      // 键不存在
      return {err, NULL};
    } }
  return {JError_OK, obj};
}
}
