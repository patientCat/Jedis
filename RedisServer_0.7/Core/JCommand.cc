#include "JCommand.hh"
#include "JDatabase.hh"
#include <muduo/net/TcpConnection.h>
#include "./Transaction/Transaction.hh"


using namespace Jedis;
using namespace muduo::net;



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
  JCommandInfo{"unwatch", -2, JCommandAttr::READ, &unwatch},
  JCommandInfo{"discard", 1, JCommandAttr::READ, &discard},
};
std::unordered_map<JString, JCommandInfo*> JCommandTable::command_handler_map_{};

void 
JCommandTable:: executeCommand(const std::vector<JString> &stringVec, ReplyType &reply)
{
  LOG_INFO << "executeCommand" ;
  LOG_TRACE << "param size = " << stringVec.size();
  if(stringVec.empty())
    return ;
  auto cmd = stringVec[0];
  // 获取命令信息
  auto command_info = getCommandHandlerMap(cmd);
  JError err;

  // 检查命令参数
  if((err = checkCommand(command_info, stringVec, reply)) 
      != JError_OK)
  {
    reply.setReply(err); 
    return ;
  }


    // 将命令和params分离
    auto iter = std::next(stringVec.begin());
    std::vector<std::string> params(iter, stringVec.end());

    
    JCommandAttr attr = command_info->attr;
    if(attr == JCommandAttr::WRITE)
    {
      std::string key = params.front(); 
      auto connection_set_ptr = G_JDataBase->getConnectionSetOf(key);
      for(TcpConnectionPtr each_conn : *connection_set_ptr)
      {
        Jedis::detail::setTransactionDirtyCas(each_conn);
      }
    }
    err = command_info->handler(params, reply);
    if(err == JError_OK && command_info->attr == JCommandAttr::READ)
    {
      return ;
    }
    reply.setReply(err); 
}
