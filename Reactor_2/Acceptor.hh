#ifndef __Accept_hh__
#define __Accept_hh__

#include "Socket.hh"
#include "Event.hh"
#include <functional>

class EventLoop;

class Acceptor
{
public:
  using AcceptHandler = std::function<void(int)>;
  explicit Acceptor(EventLoop* loop, const SocketAddr& addr)
    : loop_(loop)
    , addr_(addr)
    , socket_(Socket::CreateNonBlockTCPSocket())
  {
    Socket::SetReuseAddr(socket_.FD());
    Socket::Bind(socket_.FD(), addr);
    Socket::Listen(socket_.FD());
    FileEventPtr eventPtr = std::make_shared<FileEvent>(loop_, socket_.FD());
    eventPtr->RegisterReadHandler(std::bind(&Acceptor::OnAcceptHandler, this));
  }
  void OnAcceptHandler()
  {
    int cfd = Socket::Accept(socket_.FD());
    Socket::SetNonBlock(cfd);
    onAcceptHandler_(cfd);
  }
  void RegisterOnAcceptHandler(AcceptHandler handler)
  {
    onAcceptHandler_ = handler;
  }
private:
  EventLoop *loop_;
  SocketAddr addr_;
  Socket socket_;
  AcceptHandler onAcceptHandler_; 
};
#endif
