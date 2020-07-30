//c++ program
//design by >^.^<
//@date    2020-01-04 05:00:48
#include "./Base/TcpServer.hh"
#include "./Core/JCommand.hh"
#include "./Base/Logging.hh"
#include "TelnetCodec.hh"
#include <iostream>
#include <string>

using namespace std;
using namespace std::placeholders;
using namespace Jedis;

class JedisServer
{
public:
  JedisServer(const SocketAddr& addr)
    : server_(addr)
    , telnetCodec_(std::bind(&JedisServer::onMessage, this, _1, _2, _3))
  {
    server_.SetConnectionCallback(std::bind(&JedisServer::onConnection, this, _1));
    server_.SetMessageCallback(std::bind(&TelnetCodec::onMessage, &telnetCodec_, _1, _2, _3));
  }

  void onConnection(const TcpConnectionPtr& conn)
  {
  }

  // 这里实际上就是收到了解析的函数
  void onMessage(const TcpConnectionPtr& conn, const std::vector<std::string> &stringVec, Timestamp recvTime)
  {
    LOG_INFO << "jedis onMessage";
    std::string cmd = stringVec[0];

    ReplyType reply;
    JCommandTable::executeCommand(stringVec, reply);
    reply.put('\n');

    conn->Send(reply.str().data(), reply.str().size());
  }

 void init()
  {
    // 信号忽略
    // TODO
    JCommandTable::init();
  }
  void start()
  {
    init();
    server_.Start();
  }
private:
  TcpServer server_;
  TelnetCodec telnetCodec_;
};

int main()
{
  Logger::setLogLevel(Logger::TRACE);
  SocketAddr addr("127.0.0.1:8888");
  JedisServer server(addr);
  server.start();
}
