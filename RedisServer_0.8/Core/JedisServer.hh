//c++ program
//design by >^.^<
//@date    2020-07-28 07:16:01
#include <iostream>
#include "../Base/TcpServer.hh"
#include "../Base/TcpConnection.hh"
#include "../Base/Reactor.hh"
#include "../Base/Socket.hh"
#include "../Base/Buffer.hh"
#include "../Base/Timestamp.hh"

#include "JCommand.hh"
#include "JCurrent.hh"
#include "JConnectionContext.hh"

#include "TelnetCodec.hh"
#include <vector>
#include <string>



using namespace std::placeholders;
using namespace Jedis;

class JedisServer
{
  public:
    JedisServer(const SocketAddr &address)
      : addr_(address)
        , codec_(std::bind(&JedisServer::onMessage, this, _1, _2, _3))
        , loop_()
        , server_(&loop_, address, "JedisServer")

  {
    server_.set_connection_callback(std::bind(&JedisServer::onConnection, this, _1));
    server_.set_message_callback(std::bind(&TelnetCodec::onMessage, &codec_, _1, _2, _3));
  }

    void onConnection(const TcpConnectionPtr &conn)
    {
      if(conn->is_connected())
      {
        conn->set_context(std::make_shared<JConnectionContext>());
        LOG_INFO << "[" << conn->sock_addr().to_string() << "]" << "is connected";
      }
      if(conn->is_disconnected())
      {
        LOG_INFO << "[" << conn->sock_addr().to_string() << "]" << "is disconnected";
      }
    }
    void onMessage(const TcpConnectionPtr& conn, const  std::vector<std::string>& stringVec, Timestamp recvTime)
    {
      LOG_INFO << "jedis onMessage";

      // set curentTcpConnection
      JCurrent::CurrentTcpConnection(conn);

      std::shared_ptr<JConnectionContext>  context = std::any_cast<std::shared_ptr<JConnectionContext>>(conn->get_context());
      JTransaction &transaction = context->get_transaction();

      JReply reply;
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
      LOG_INFO << addr_.to_string() << " is listening" ;
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

    SocketAddr addr_;
    TelnetCodec codec_;
    Reactor loop_;
    TcpServer server_;
};
