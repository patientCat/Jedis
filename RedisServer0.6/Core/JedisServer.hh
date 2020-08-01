//c++ program
//design by >^.^<
//@date    2020-07-28 07:16:01
#include <iostream>
#include "muduo/net/TcpServer.h"
#include "muduo/net/TcpConnection.h"
#include "muduo/net/EventLoop.h"
#include "muduo/net/InetAddress.h"
#include "muduo/net/Buffer.h"
#include "muduo/base/Timestamp.h"

#include "JCommand.hh"
#include "JCurrent.hh"
#include "JConnectionContext.hh"

#include "TelnetCodec.hh"
#include "boost/format.hpp"
#include <vector>
#include <string>


using namespace muduo;
using namespace muduo::net;

using namespace std::placeholders;
using namespace Jedis;

class JedisServer
{
  public:
    JedisServer(const InetAddress &address)
      : addr_(address)
        , codec_(std::bind(&JedisServer::onMessage, this, _1, _2, _3))
        , loop_()
        , server_(&loop_, address, "JedisServer")

  {
    server_.setThreadNum(1);
    server_.setConnectionCallback(std::bind(&JedisServer::onConnection, this, _1));
    server_.setMessageCallback(std::bind(&TelnetCodec::onMessage, &codec_, _1, _2, _3));
  }

    void onConnection(const TcpConnectionPtr &conn)
    {
      if(conn->connected())
      {
        conn->setContext(std::make_shared<JConnectionContext>());
        string info =  (boost::format("[%s] is connected") % conn->peerAddress().toIpPort()).str() ;
        LOG_INFO << info;
      }
      else{
        string info =  (boost::format("[%s] is disconnected") % conn->peerAddress().toIpPort()).str() ;
        LOG_INFO << info;
      }
    }
    void onMessage(const TcpConnectionPtr& conn, const  std::vector<std::string>& stringVec, muduo::Timestamp recvTime)
    {
      LOG_INFO << "jedis onMessage";

      // set curentTcpConnection
      Current::CurrentTcpConnection(conn); 

      std::shared_ptr<JConnectionContext>  context = boost::any_cast<std::shared_ptr<JConnectionContext>>(conn->getContext());
      JTransaction &transaction = context->get_transaction();

      ReplyType reply;
      if(transaction.is_mult())
      {
        transaction.executeCommandIsMulti(stringVec, reply);
      }
      else{ 
        JCommandTable::executeCommand(stringVec, reply);
      }

      codec_.send(conn, reply.getString());
    }

    void start()
    {
      init();
      LOG_INFO << addr_.toIpPort() << " is listening" ;
        server_.start();
      loop_.loop();
    }
  private:
    void init()
    {
      // 信号忽略
      // TODO
      JCommandTable::init();
    }

    InetAddress addr_;
    TelnetCodec codec_;
    EventLoop loop_;
    TcpServer server_;
};
