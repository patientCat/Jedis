#include "JCommand.hh"
#include "../Base/TcpConnection.hh"
#include "./Transaction/JTransaction.hh"
#include "JDatabase.hh"

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

        JCommandInfo{"zadd", -4, JCommandAttr::WRITE, &zadd},
        JCommandInfo{"zcard", 2, JCommandAttr::READ, &zcard},
        JCommandInfo{"zrank", 3, JCommandAttr::READ, &zrank},
        JCommandInfo{"zscore", 3, JCommandAttr::READ, &zscore},
        JCommandInfo{"zrange", -4, JCommandAttr::READ, &zrange},

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
JCommandTable:: executeCommand(const std::vector<JString> &stringVec,
                               JReply &reply)
{
  LOG_INFO << "executeCommand" ;
  LOG_TRACE << "param size = " << stringVec.size();
  if(stringVec.empty())
    return ;
  auto cmd = stringVec[0];
  // 获取命令信息
  auto command_info = getCommandHandlerMap(cmd);
  if(command_info)
  {
    LOG_INFO<< "cmd exist" << " cmd is" << cmd;
  }else{
    LOG_INFO<< "cmd not exist" << " cmd is" << cmd;
  }

  // 检查命令参数
  auto is_ok = checkCommand(command_info, stringVec, reply);
  if(!is_ok)
  {
    return ;
  }


  // 将命令和params分离
  auto iter = std::next(stringVec.begin());
  std::vector<Jedis::JString> params(iter, stringVec.end());


  JCommandAttr attr = command_info->attr;
  if(attr == JCommandAttr::WRITE)
  {
    Jedis::JString key = params.front();
    // 获得key对应的监视connection set
    auto connection_set_ptr = G_JDataBase->getConnectionSetOf(key);
    if(connection_set_ptr){
      for(TcpConnectionPtr each_conn : *connection_set_ptr)
      {
        Jedis::detail::setTransactionDirtyCas(each_conn);
      }
    }
  }
  is_ok = command_info->handler(params, reply);
  if(is_ok && command_info->attr == JCommandAttr::READ)
  {
    return ;
  }else{
    // 命令执行失败的处理是什么
  }
}
