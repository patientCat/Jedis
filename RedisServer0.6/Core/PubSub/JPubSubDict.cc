//c++ program
//design by >^.^<
//@date    2020-07-30 04:38:59

#include "JPubSubDict.hh"
#include "../JCommand.hh"
#include "../Current.hh"

#include <vector>
#include "../JParams.hh"
#include "muduo/base/Logging.h"

using namespace Jedis;

namespace  Jedis{
// 实现订阅
//

JError subscribe (const std::vector<Jedis::JString>& params, ReplyType &reply)
{
  LOG_TRACE << "subscribe";
  // 要获取当前连接
  auto conn = Current::CurrentTcpConnection();
  for(const auto & channel_name : params)
  {
      JPubSubDict::Instance().subscribe(channel_name, conn);
  }
    // TODO: 返回成功订阅的数目和name
  reply.setReply(JError_OK);
  return JError_OK;
}

// 实现取消订阅
JError unsubscribe (const std::vector<Jedis::JString>& params, ReplyType &reply)
{
    auto conn = Current::CurrentTcpConnection();
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
    reply.setReply(JError_OK);
    return JError_OK;
}

// 实现发布
JError publish (const std::vector<Jedis::JString>& params, ReplyType &reply)
{
   auto conn = Current::CurrentTcpConnection();
   auto &pubSubDict = JPubSubDict::Instance();
   auto &channel_name = params[JPos::JKeyPos];
   auto &message = params[JPos::JParamPos];
   pubSubDict.publish(channel_name, message, Timestamp::now());
   reply.setReply(JError_OK);
   return JError_OK;
}

}// namespace Jedis
