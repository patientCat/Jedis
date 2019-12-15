//c++ program
//design by >^.^<
//@date    2019-12-15 02:21:02
#include <iostream>
#include "EventLoop.hh"
#include "TcpConnection.hh"

int main()
{
  EventLoop loop;
  SocketAddr addr("127.0.0.1:8888");
  TcpConnectionPtr conn = std::make_shared<TcpConnection>(&loop, 10, addr);
}
