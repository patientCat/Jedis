//c++ program
//design by >^.^<
//@date    2020-01-04 05:00:48
#include "./Base/TcpServer.hh"
#include <iostream>
#include <string>

using namespace std;
using namespace std::placeholders;
class EchoStringServer
{
public:
  EchoStringServer(const SocketAddr& addr)
    : server_(addr)
  {
    server_.set_write_complete_callback(std::bind(&EchoStringServer::onConnection, this, _1));
    server_.set_message_callback(std::bind(&EchoStringServer::onMessage, this, _1, _2, _3));
    server_.set_connection_callback(std::bind(&EchoStringServer::onConnection, this, _1));
  }

  void onConnection(const TcpConnectionPtr& conn)
  {
    if(conn->status() == ConnectionStatus::kConnected)
    {
      cout << "connected" << endl;
    }
    if(conn->status() == ConnectionStatus::kDisconnected)
    {
      cout << "disconnected " << endl;
    }
  }

  void onMessage(const TcpConnectionPtr& conn, Buffer *buffer, Timestamp recvTime)
  {
    conn->send("hello", strlen("hello"));
  }

  void start()
  {
    server_.Start();
  }
private:
  TcpServer server_;
};

int main()
{
  Logger::setLogLevel(Logger::TRACE);
  SocketAddr addr("127.0.0.1:8888");
  EchoStringServer server(addr);
  server.start();
}
