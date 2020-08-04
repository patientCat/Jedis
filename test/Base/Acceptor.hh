#ifndef __Accept_hh__
#define __Accept_hh__

#include "Socket.hh"
#include "Event.hh"
#include "Logging.hh"
#include <functional>

class Reactor;

class Acceptor : Noncopyable
{
public:
  using AcceptHandler = std::function<void(int)>;
  explicit Acceptor(Reactor* loop, const SocketAddr& addr)
    : loop_(loop)
    , addr_(addr)
    , socket_(Socket::create_nonblock_socket())
  {
    Socket::set_reuse_addr(socket_.fd());
    Socket::bind(socket_.fd(), addr);
    Socket::listen(socket_.fd());
    LOG_INFO << "server is listening on " << addr.to_string();
    socket_event_ptr_ = SocketEvent::new_event_handler(loop, socket_.fd());
      socket_event_ptr_->set_read_callback(std::bind(&Acceptor::on_accept, this));
      socket_event_ptr_->enable_read();
  }
  void on_accept()
  {
    LOG_DEBUG << "Acceptor accept";
    int cfd = Socket::accept(socket_.fd());
    Socket::set_nonblock(cfd);
    onAcceptHandler_(cfd);
  }
  void set_accept_callback(AcceptHandler handler)
  {
    onAcceptHandler_ = handler;
  }
private:
  Reactor *loop_;
  SocketAddr addr_;
  Socket socket_;
  AcceptHandler onAcceptHandler_; 
  SocketEventSharedPtr socket_event_ptr_;
};
#endif
