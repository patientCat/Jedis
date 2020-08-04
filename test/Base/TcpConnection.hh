#ifndef __TCPCONNECTION_HH
#define __TCPCONNECTION_HH

#include <memory>
#include "Callback.hh"
#include "Socket.hh"
#include "Buffer.hh"
#include "Event.hh"

#include <memory>
#include <iostream>
#include "Noncopyable.hh"

class Reactor;

enum class ConnectionStatus
{
  kConnected,
  kCloseRead,
  kIsDisconnecting,
  kDisconnected
};

class TcpConnection 
: Noncopyable
, public std::enable_shared_from_this<TcpConnection>
{
public: 
  TcpConnection(Reactor* loop, int fd, const SocketAddr& addr);

  void set_connection_callback(const ConnectionCallback &cb)
  {
    onConnectionCallback_ = cb;
  }
  void set_message_callback(const MessageCallback &cb)
  {
    onMessageCallback_ = cb;
  }
  void set_write_complete_callback(const WriteCompleteCallback &cb)
  {
    onWriteCompleteCallback_ = cb;
  }
  void set_close_callback(const CloseCallback &cb)
  {
    onCloseCallback_ = cb;
  };

  int fd()const{  return sock_.fd();  };


  // 这里实际上是将消息交给写Buffer，然后注册一个写函数去发送消息
  void send(const char *data, int len);

  SocketAddr sockAddr() const { return addr_; }

  void set_status(ConnectionStatus status)
  {
    status_ = status;
  }
  // @Depreicated
  ConnectionStatus status()const
  {
    return status_;
  }
  bool is_connected() const{
    return status_ == ConnectionStatus::kConnected;
  }
  bool is_disconnected() const{
    return status_ == ConnectionStatus::kDisconnected;
  }
  void connection_destroyed();
private:
  void handle_read(Timestamp recvTimePoint);
  void handle_write();
  void handle_close();
  void handle_error(int err_num)
  {
    // TODO 
    char buff[100];
    sprintf(buff, "write err err_num = %d\n", err_num);
    perror(buff);
  }
private:
  // 持有的EventLoop
  Reactor* loop_;
  Socket sock_; 
  SocketAddr addr_;

  // 读写缓冲区
  Buffer readBuffer_;
  Buffer writeBuffer_;
  SocketEventSharedPtr fileEvent_;

  // 连接一建立，就是连接状态
  ConnectionStatus status_{ConnectionStatus::kConnected};

  // 注册的回调函数
  MessageCallback onMessageCallback_;
  WriteCompleteCallback onWriteCompleteCallback_;
  ConnectionCallback onConnectionCallback_;
  CloseCallback onCloseCallback_;
};
#endif
