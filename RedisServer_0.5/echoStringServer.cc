//c++ program
//design by >^.^<
//@date    2020-01-04 05:00:48
#include "./Base/TcpServer.hh"
#include "TelnetCodec.hh"
#include <iostream>
#include <string>

using namespace std;
using namespace std::placeholders;
class EchoStringServer
{
public:
  EchoStringServer(const SocketAddr& addr)
    : server_(addr)
    , telnetCodec_(std::bind(&EchoStringServer::onMessage, this, _1, _2, _3))
  {
    server_.SetConnectionCallback(std::bind(&EchoStringServer::onConnection, this, _1));
    server_.SetMessageCallback(std::bind(&TelnetCodec::onMessage, &telnetCodec_, _1, _2, _3));
  }

  void onConnection(const TcpConnectionPtr& conn)
  {
    if(conn->status() == ConnectionStatus::kDisconnected)
    {
      cout << "connection callback " << endl;
    }
  }

  void onMessage(const TcpConnectionPtr& conn, const std::vector<std::string> &stringVec, Timestamp recvTime)
  {
    vector<string> vec{"hello", "world"};
    telnetCodec_.send(conn, vec);
  }

  void start()
  {
    server_.Start();
  }
private:
  TcpServer server_;
  TelnetCodec telnetCodec_;
};

int main()
{
  SocketAddr addr("127.0.0.1:8888");
  EchoStringServer server(addr);
  server.start();
}
