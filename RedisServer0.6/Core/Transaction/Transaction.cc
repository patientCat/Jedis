//c++ program
//design by >^.^<
//@date    2020-07-30 07:37:20
#include "Transaction.hh"

#include "../JCommand.hh"
#include "../Current.hh"


namespace Jedis{

  // 事务开始
JError multi(const std::vector<Jedis::JString>& , ReplyType &reply)
{
  auto conn = Current::CurrentTcpConnection();
  auto status = Current::CurrentTcpConnectionStatus();
  assert(conn && status); // 当前连接和其状态一定存在

  if(status->is_multi_flag)
  {
    // 如果事务已经开启，返回错误
    return JError_InvalidType;
  }

  auto &transaction = Transaction::Instance();
  transaction.multi(status);
  return JError_OK;
}

JError exec(const std::vector<Jedis::JString>& , ReplyType &reply)
{
}

JError watch(const std::vector<Jedis::JString>& , ReplyType &reply)
{
}

}// namespace Jedis

void 
Transaction::multi(ConnectionStatus * s)
{
  s->is_multi_flag = true;
}
