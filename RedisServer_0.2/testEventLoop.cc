//c++ program
//design by >^.^<
//@date    2019-12-02 04:15:25
#include "Socket.hh"
#include "EventLoop.hh"
#include "Event.hh"
#include "Acceptor.hh"

#include <iostream>
#include <memory>
// 测试EventLoop, 简单写一个echo服务器
using namespace std;

class Server
{
public:
  Server(const SocketAddr& addr)
    : addr_(addr)
    , loop_()
    , acceptor_(&loop_, addr)
  {
    acceptor_.RegisterOnAcceptHandler(std::bind(&Server::OnAcceptHandle, this, placeholders::_1));
  }

  void OnReading(int fd)
  {
    char buff[1024] = {0};
    ::read(fd, buff, 1024);
    ::write(fd, buff, strlen(buff));
  }

  void OnAcceptHandle(int cfd)
  {
    auto event = make_shared<FileEvent>(&loop_, cfd);
    event->RegisterReadHandler(std::bind(&Server::OnReading, this, placeholders::_1));
    event->EnableReading();
  }

  void Start()
  {
    loop_.Loop();
  }
private:
  SocketAddr addr_;
  EventLoop loop_;
  Acceptor acceptor_;
};



int main()
{
  SocketAddr addr("127.0.0.1:8888");
  Server jedis(addr); 
  jedis.Start();
}
