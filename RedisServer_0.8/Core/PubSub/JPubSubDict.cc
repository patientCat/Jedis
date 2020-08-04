//c++ program
//design by >^.^<
//@date    2020-07-30 04:38:59

#include "JPubSubDict.hh"
#include "../JCommand.hh"
#include "../JCurrent.hh"

#include "../JParams.hh"
#include "../../Base/Logging.hh"
#include <vector>

using namespace Jedis;

namespace  Jedis{
// 实现订阅
//

bool subscribe (const std::vector<Jedis::JString>& params, JReply &reply)
{
  LOG_TRACE << "subscribe";
  // 要获取当前连接
  auto conn = JCurrent::CurrentTcpConnection();
  for(const auto & channel_name : params)
  {
      JPubSubDict::Instance().subscribe(channel_name, conn);
  }
    // TODO: 返回成功订阅的数目和name
  reply.setReply();
  return true;
}

// 实现取消订阅
bool unsubscribe (const std::vector<Jedis::JString>& params, JReply &reply)
{
    auto conn = JCurrent::CurrentTcpConnection();
    auto &pubSubDict = JPubSubDict::Instance();
    if(params.empty())
    {
       // pubSubDict.unSubscribe(conn); // 取消订阅所有channel
    }else{
       for(auto & channel_name : params)
       {
           pubSubDict.unSubscribe(channel_name, conn);
       }
    }
    // TODO: 返回取消订阅的数目
    reply.setReply();
    return true;
}

// 实现发布
bool publish (const std::vector<Jedis::JString>& params, JReply &reply)
{
   auto conn = JCurrent::CurrentTcpConnection();
   auto &pubSubDict = JPubSubDict::Instance();
   auto &channel_name = params[JPos::JKeyPos];
   auto &message = params[JPos::JParamPos];
   pubSubDict.publish(channel_name, message, Timestamp::now());
   reply.setReply();
   return true;
}

}// namespace Jedis
