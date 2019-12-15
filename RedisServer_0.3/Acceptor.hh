#ifndef __Accept_hh__
#define __Accept_hh__

#include "Socket.hh"
#include "Event.hh"
#include "Logging.hh"
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
    LOG_DEBUG << "server is listening on " << addr.ToString();
    fePtr_ = FileEvent::NewFileEvent(loop, socket_.FD());
    fePtr_->RegisterReadHandler(std::bind(&Acceptor::OnAcceptHandler, this));
    fePtr_->EnableReading();
  }
  void OnAcceptHandler()
  {
    LOG_DEBUG << "Acceptor accept";
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
  FileEventPtr fePtr_;
};
#endif
