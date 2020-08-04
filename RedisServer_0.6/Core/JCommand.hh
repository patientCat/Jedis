#ifndef __JCOMMAND_HH__
#define __JCOMMAND_HH__

#include "./Object/JString.hh"
#include "JError.hh"
#include "JReply.hh"

#include "../Base/Logging.hh"

#include <functional>
#include <vector>
#include <unordered_map>
#include <sstream>

namespace Jedis{

using JCommandHandler = JError (const std::vector<Jedis::JString>& , ReplyType &reply);

// JString

JCommandHandler set;
JCommandHandler setnx;
JCommandHandler get;

// JList
JCommandHandler lpush;
JCommandHandler rpush;
JCommandHandler lrange;

// sub/pub
JCommandHandler subscribe;
JCommandHandler unsubscribe;
JCommandHandler publish;

// 事务
JCommandHandler multi;
JCommandHandler exec;
JCommandHandler watch;
JCommandHandler unwatch;
JCommandHandler discard;

enum class JCommandAttr
{
  READ,
  WRITE
};

struct JCommandInfo
{
  Jedis::JString cmd_name;
  int para_num;
  JCommandAttr attr; 
  JCommandHandler *handler;
};

class JCommandTable
{
  using CommandHandlerMap = std::unordered_map<JString, JCommandInfo*>;

  // 用来check command的合理性
  static JError checkCommand(JCommandInfo *command_info, const std::vector<JString> &stringVec, ReplyType &reply)
  {
    LOG_TRACE << "step into func checkCommand ";
    if(!command_info)
    {
      return JError_CmdNotExist;
    }
    if(command_info->para_num > 0)
    {
      if(command_info->para_num != stringVec.size())
        return JError_ParamNum;
    }else{
      // <0
      int num = -1 * command_info->para_num;
      if(stringVec.size() < num)
      {
        return JError_ParamNum;
      }
    }
    return JError_OK;
  }

public:
  // 初始化表
  static void init()
  {
    LOG_DEBUG << "初始化全局命令表" ;
    // 从vec中初始化map
    for(int i = 0; i < command_info_vec_.size(); i++)
    {
      command_handler_map_[command_info_vec_[i].cmd_name] = &command_info_vec_[i]; 
    }
  }
  static void executeCommand(const std::vector<JString> &stringVec, ReplyType &reply);

  // get commandinfo
  static JCommandInfo* getCommandHandlerMap(const JString &key)
  {
    if(command_handler_map_.count(key))
      return command_handler_map_[key];
    else
      return NULL;
  }

private:
  static std::vector<JCommandInfo> command_info_vec_;
  static std::unordered_map<JString, JCommandInfo*> command_handler_map_;
};
}
#endif
