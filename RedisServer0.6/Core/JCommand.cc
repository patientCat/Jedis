#include "JCommand.hh"


using namespace Jedis;



// 参数个数 正数用来精准匹配，负数用来带表至少多少个
std::vector<JCommandInfo> JCommandTable::command_info_vec_ 
{
  JCommandInfo{"set", 3, JCommandAttr::WRITE, &set},
  JCommandInfo{"setnx", 3, JCommandAttr::WRITE, &setnx},
  JCommandInfo{"get", 2, JCommandAttr::READ, &get},

  JCommandInfo{"lpush", -3, JCommandAttr::WRITE, &lpush},
  JCommandInfo{"rpush", -3, JCommandAttr::WRITE, &rpush},
  JCommandInfo{"lrange", 4, JCommandAttr::READ, &lrange},

  JCommandInfo{"subscribe", -2, JCommandAttr::READ, &subscribe},
  JCommandInfo{"unsubscribe", -1, JCommandAttr::READ, &unsubscribe},
  JCommandInfo{"publish", 3, JCommandAttr::READ, &publish},

  JCommandInfo{"multi", 1, JCommandAttr::READ, &multi},
  JCommandInfo{"exec", 1, JCommandAttr::READ, &exec},
  JCommandInfo{"watch", -2, JCommandAttr::READ, &watch},
};
std::unordered_map<JString, JCommandInfo*> JCommandTable::command_handler_map_{};
