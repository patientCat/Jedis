//c++ program
//design by >^.^<
//@date    2020-07-30 07:37:20
#include "Transaction.hh"

#include "../JCommand.hh"
#include "../JCurrent.hh"
#include "../JConnectionContext.hh"
#include "../JReply.hh"
#include "../JDatabase.hh"

#include <muduo/net/TcpConnection.h>

using namespace muduo::net;
namespace Jedis{

  
  namespace {
  JTransaction &getConnectionTransaction(const TcpConnectionPtr &conn)
  {
  auto conn_context = boost::any_cast<std::shared_ptr<JConnectionContext>>(conn->getContext());
  return conn_context->get_transaction();
  }

  JTransaction &getCurrConnectionTransaction()
  {
  auto conn = Current::CurrentTcpConnection();
  assert(conn); // 当前连连接

  auto conn_context = boost::any_cast<std::shared_ptr<JConnectionContext>>(conn->getContext());
  return conn_context->get_transaction();
  }
  }

  namespace detail{
    void setTransactionDirtyCas(const std::shared_ptr<muduo::net::TcpConnection> &conn)
    {
      auto &transaction = getConnectionTransaction(conn);
      transaction.set_dirty();
    }
  }

  // 事务开始
JError multi(const std::vector<Jedis::JString>& , ReplyType &reply)
{
  auto &transaction = getCurrConnectionTransaction();
  if(transaction.is_mult())
  {
    // 如果事务已经开启，返回错误
    return JError_InvalidType;
  }
  transaction.multi();
  reply.setReply(JError_OK);
  return JError_OK;
}

JError exec(const std::vector<Jedis::JString>& , ReplyType &reply)
{
  auto &transaction = getCurrConnectionTransaction();
  if(!transaction.is_mult())
  {
    // 如果事务没有开启，返回错误
    return JError_InvalidType;
  }
  if(transaction.is_dirty())
  {
    // 事务失败
    char *str = "exec error because key is dirty";
    reply.setReply(str, strlen(str));
    return JError_DirtyCas;
  }
  transaction.exec(reply);
  reply.setReply(JError_OK);
  return JError_OK;
}

JError watch(const std::vector<Jedis::JString>& keys, ReplyType &reply)
{
  auto &transaction = getCurrConnectionTransaction();

  transaction.watch(keys);
  reply.setReply(JError_OK);
  return JError_OK;
}

JError unwatch(const std::vector<Jedis::JString>& keys, ReplyType &reply)
{
  auto &transaction = getCurrConnectionTransaction();
  reply.setReply(JError_OK);
  transaction.unwatch(keys);
  return JError_OK;
}
JError discard(const std::vector<Jedis::JString>& , ReplyType &reply)
{
  auto &transaction = getCurrConnectionTransaction();
  transaction.discard();
  reply.setReply(JError_OK);
  return JError_OK;
}

void 
JTransaction::executeCommandIsMulti(const StringVec& stringvec, Jedis::ReplyType &reply)
{
    std::string cmd = stringvec[0];
    // 将cmd转小写
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), [](char x){
        return tolower(x);
        });


    if(!cmd.compare("exec") 
        || !cmd.compare("multi") 
        || !cmd.compare("watch") 
        || !cmd.compare("unwatch")
        || !cmd.compare("discard")
        )
    {
      // 如果是exec命令，就去命令表调用exec命令
      JCommandTable::executeCommand(stringvec, reply);
    }else{
      push_packet(stringvec);
      reply.setReply("queued", strlen("queued"));
    }
}

void
JTransaction::watch(const StringVec& keys)
{
   // 将监视的key的conn存放起来
   auto conn = Current::CurrentTcpConnection();
   for(const auto&each_key : keys)
   {
     G_JDataBase->addConnectionInWatchedKeys(each_key, conn);
   }
}

void
JTransaction::handle_packet(const StringVec& packet, ReplyType &reply)
{
  JCommandTable::executeCommand(packet, reply);
}
}// namespace Jedis
