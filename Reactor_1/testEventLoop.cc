//c++ program
//design by >^.^<
//@date    2019-12-02 04:15:25
#include "Socket.hh"
#include "EventLoop.hh"
#include "Event.hh"

#include <iostream>
#include <memory>
// 测试EventLoop, 简单写一个echo服务器
using namespace std;

EventLoop eventLoop;

void onReading(int fd)
{
  char buff[1024] = {0};
  ::read(fd, buff, 1024);
  ::write(fd, buff, strlen(buff));
}

void onAccept(int fd)
{
  cout << "accept" << endl;
  int connfd = Socket::Accept(fd);
  auto event = make_shared<FileEvent>(connfd);
  event->RegisterReadHandler(onReading);
  eventLoop.RegisterFileEvent(event);
}

int main()
{
  Socket s(Socket::CreateTCPSocket());
  SocketAddr addr("127.0.0.1:8888");
  Socket::Bind(s.FD(), addr);
  Socket::Listen(s.FD());
  auto event = make_shared<FileEvent>(s.FD());
  event->RegisterReadHandler(onAccept);

  eventLoop.RegisterFileEvent(event);
  eventLoop.Loop();
}
