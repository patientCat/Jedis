#ifndef __TCPCONNECTION_HH
#define __TCPCONNECTION_HH

#include <memory>
#include "Callback.hh"
#include "Socket.hh"
#include "Buffer.hh"
#include "Event.hh"

#include <memory>
#include <iostream>

class EventLoop;

enum ConnectionStatus
{
  kIntial,
  kConnected,
  kDisconnected
};
class TcpConnection 
: boost::noncopyable
, public std::enable_shared_from_this<TcpConnection>
{
public: 
  TcpConnection(EventLoop* loop, int fd, const SocketAddr& addr)
    : loop_(loop)
    , sock_(fd)
    , addr_(addr)
    , fileEvent_(FileEvent::NewFileEvent(loop, fd))
  {
    fileEvent_->RegisterReadHandler(std::bind(&TcpConnection::handleRead, this, std::placeholders::_1));
    fileEvent_->RegisterWriteHandler(std::bind(&TcpConnection::handleWrite, this));
    fileEvent_->EnableReading();
  }

  void SetConnectionCallback(const ConnectionCallback &cb)
  {
    onConnectionCallback_ = cb;
  }
  void SetMessageCallback(const MessageCallback &cb)
  {
    onMessageCallback_ = cb;
  }
  void SetWriteCompleteCallback(const WriteCompleteCallback &cb)
  {
    onWriteCompleteCallback_ = cb;
  }
  void SetCloseCallback(const CloseCallback &cb)
  {
    onCloseCallback_ = cb;
  };
  int FD()const{  return sock_.FD();  };


  // 这里实际上是将消息交给写Buffer，然后注册一个写函数去发送消息
  void Send(const char *data, int len);

  SocketAddr Addr() const { return addr_; }

  void setStatus(ConnectionStatus status)
  {
    status_ = status;
  }
  ConnectionStatus status()const
  {
    return status_;
  }
  void connectionDestroyed();
private:
  void handleRead(Timestamp recvTimePoint);
  void handleWrite();
  void handleClose();
private:
  EventLoop* loop_;
  Socket sock_; 
  SocketAddr addr_;
  Buffer readBuffer_;
  Buffer writeBuffer_;
  FileEventPtr fileEvent_;
  ConnectionStatus status_{kIntial};

  MessageCallback onMessageCallback_;
  WriteCompleteCallback onWriteCompleteCallback_;
  ConnectionCallback onConnectionCallback_;
  CloseCallback onCloseCallback_;
};
#endif
