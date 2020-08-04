//c++ program
//design by >^.^<
//@date    2020-07-30 07:37:20
#include "JTransaction.hh"

#include "../JCommand.hh"
#include "../JCurrent.hh"
#include "../JConnectionContext.hh"
#include "../JDatabase.hh"


namespace Jedis{


  namespace {
    JTransaction &getConnectionTransaction(const TcpConnectionPtr &conn)
    {
      auto conn_context = std::any_cast<std::shared_ptr<JConnectionContext>>(conn->get_context());
      return conn_context->get_transaction();
    }

    JTransaction &getCurrConnectionTransaction()
    {
      auto conn = JCurrent::CurrentTcpConnection();
      assert(conn); // 当前连连接

      auto conn_context = std::any_cast<std::shared_ptr<JConnectionContext>>(conn->get_context());
      return conn_context->get_transaction();
    }
  }// end namespace unkown

  namespace detail{
    void setTransactionDirtyCas(const std::shared_ptr<TcpConnection> &conn)
    {
      auto &transaction = getConnectionTransaction(conn);
      transaction.set_dirty();
    }
  }

  // 事务开始
  bool multi(const std::vector<Jedis::JString>& , JReply &reply)
  {
    auto &transaction = getCurrConnectionTransaction();
    if(transaction.is_mult())
    {
      reply.setReply(JReply::JReplyType::Duplicate_Multi);
      return false;
    }
    transaction.multi();
    reply.setReply();
    return true;
  }

  bool exec(const std::vector<Jedis::JString>& , JReply &reply)
  {
    auto &transaction = getCurrConnectionTransaction();
    if(!transaction.is_mult())
    {
      // 如果事务没有开启，返回错误
      JString info = "没有开启事务";
      reply.setReply(info );
      return false;
    }
    if(transaction.is_dirty())
    {
      // 事务失败
      JString str = "事务执行失败，观察的key被修改了";
      reply.setReply(str);
      return false;
    }
    transaction.exec(reply);
    reply.setReply();
    return true;
  }

  bool watch(const std::vector<Jedis::JString>& keys, JReply &reply)
  {
    auto &transaction = getCurrConnectionTransaction();

    transaction.watch(keys);
    reply.setReply();
    return true;
  }

  bool unwatch(const std::vector<Jedis::JString>& keys, JReply &reply)
  {
    auto &transaction = getCurrConnectionTransaction();
    reply.setReply();
    transaction.unwatch(keys);
    return true;
  }
  bool discard(const std::vector<Jedis::JString>& , JReply &reply)
  {
    auto &transaction = getCurrConnectionTransaction();
    transaction.discard();
    reply.setReply();
    return true;
  }

  void 
    JTransaction::executeCommandIsMulti(const StringVec& stringvec, Jedis::JReply &reply)
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
      auto conn = JCurrent::CurrentTcpConnection();
      for(const auto&each_key : keys)
      {
        G_JDataBase->addConnectionInWatchedKeys(each_key, conn);
      }
    }

  void
    JTransaction::handle_packet(const StringVec& packet, JReply &reply)
    {
      JCommandTable::executeCommand(packet, reply);
    }
}// namespace Jedis
