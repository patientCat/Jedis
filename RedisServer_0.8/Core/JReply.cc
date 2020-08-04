//c++ program
//design by >^.^<
//@date    2020-06-24 08:51:20
#include "JReply.hh"
#include "JDatabase.hh"
#include "../Base/Logging.hh"


using namespace Jedis;


const Jedis::JString JReply::kErrDuplicateMultStr{"重复开启事务"};
const Jedis::JString JReply::kErrMismatchTypeStr{"类型不匹配"};
const Jedis::JString JReply::kErrKeyAleadyExistStr{"key已经存在"};
const Jedis::JString JReply::kErrKeyNotExistStr{"key不存在"};
const Jedis::JString JReply::kErrInvalidType{"无效的类型，代码错误"};
const Jedis::JString JReply::kErrParamsNum{"参数数量错误"};
const Jedis::JString JReply::kErrCmdNotExist{"命令不存在"};
const Jedis::JString JReply::kErrInvalidParamFormat{"参数格式错误"};
const Jedis::JString JReply::kErrOk{"OK"};
const Jedis::JString JReply::kJianTou{"--->"};

