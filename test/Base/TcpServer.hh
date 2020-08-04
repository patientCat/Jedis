#ifndef __TCPSERVER_HH__
#define __TCPSERVER_HH__

#include "Reactor.hh"
#include "Socket.hh"
#include "Acceptor.hh"
#include "TcpConnection.hh"
#include "Logging.hh"
#include "Noncopyable.hh"

#include <functional>
#include <unordered_map>


class TcpServer
: Noncopyable
{
    static TcpServer * instance_;
public:
    static TcpServer *getInstance()
    {
        if(instance_ == nullptr)
        {
            LOG_ERROR << "服务器没有被创建，请先创建服务器" ;
        }
        return instance_;
    }
    // TODO 只能做一个TcpServer， 并且设置一个单例
  TcpServer(const SocketAddr& addr)
    : eventLoop_()
    , acceptor_(&eventLoop_, addr)
    , addr_(addr)
  {
      acceptor_.set_accept_callback(std::bind(&TcpServer::on_new_connection, this, std::placeholders::_1));
  }

  void set_connection_callback(ConnectionCallback callback)
  {
    connectionCallback_ = callback;
  }
  void set_message_callback(MessageCallback callback)
  {
    messageCallback_ = callback;
  }
  void set_write_complete_callback(WriteCompleteCallback callback)
  {
    writeCallback_ = callback;
  }

  void Start()
  {
      eventLoop_.loop();
  }

private:
  void on_new_connection(int cfd);
  void remove_connection_in_loop(const TcpConnectionPtr& ptr);
  void remove_connection(const TcpConnectionPtr& ptr);
private:
  std::unordered_map<int, TcpConnectionPtr> tcpConnectionPtrList_;  
  Reactor eventLoop_;
  Acceptor acceptor_;
  SocketAddr addr_;

  ConnectionCallback connectionCallback_;
  MessageCallback messageCallback_;
  WriteCompleteCallback writeCallback_;
};
#endif
