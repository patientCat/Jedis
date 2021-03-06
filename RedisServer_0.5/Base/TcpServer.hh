#ifndef __TCPSERVER_HH__
#define __TCPSERVER_HH__

#include "EventLoop.hh"
#include "Socket.hh"
#include "Acceptor.hh"
#include "TcpConnection.hh"
#include "Logging.hh"
#include <boost/noncopyable.hpp>

#include <functional>
#include <unordered_map>


class TcpServer
: boost::noncopyable
{
public:
  TcpServer(const SocketAddr& addr)
    : eventLoop_()
    , acceptor_(&eventLoop_, addr)
    , addr_(addr)
  {
    acceptor_.RegisterOnAcceptHandler(std::bind(&TcpServer::onNewConnection, this, std::placeholders::_1));
  }

  void SetConnectionCallback(ConnectionCallback callback)
  {
    connectionCallback_ = callback;
  }
  void SetMessageCallback(MessageCallback callback)
  {
    messageCallback_ = callback;
  }
  void SetWriteCompleteCallback(WriteCompleteCallback callback)
  {
    writeCallback_ = callback;
  }

  void Start()
  {
    eventLoop_.Loop();
  }

private:
  void onNewConnection(int cfd)
  {
    SocketAddr peerAddr;
    Socket::GetPeerAddr(cfd, peerAddr);
    LOG_INFO << "new connection " << peerAddr.ToString() << " is established";
    TcpConnectionPtr ptr(new TcpConnection(&eventLoop_, cfd, peerAddr));
    tcpConnectionPtrList_[cfd] = ptr;
    ptr->setStatus(ConnectionStatus::kConnected);

    if(connectionCallback_)
      connectionCallback_(ptr);
    // 这里需要注册TcpConnection的回调函数
    
    ptr->SetConnectionCallback(connectionCallback_);
    ptr->SetMessageCallback(messageCallback_);
    ptr->SetWriteCompleteCallback(writeCallback_);
    ptr->SetCloseCallback(std::bind(&TcpServer::removeConnection, this, std::placeholders::_1));
  }

  void removeConnectionInLoop(const TcpConnectionPtr& ptr)
  {
    int fd = ptr->FD(); 
    // auto copy = ptr;
    tcpConnectionPtrList_.erase(fd);

    eventLoop_.RunAfterPoll(std::bind(&TcpConnection::connectionDestroyed, ptr)); 
  }
  void removeConnection(const TcpConnectionPtr& ptr)
  {
    LOG_DEBUG << "remove Connection";
    eventLoop_.RunAfterPoll(std::bind(&TcpServer::removeConnectionInLoop, this, ptr));
  }
private:
  std::unordered_map<int, TcpConnectionPtr> tcpConnectionPtrList_;  
  EventLoop eventLoop_;
  Acceptor acceptor_;
  SocketAddr addr_;

  ConnectionCallback connectionCallback_;
  MessageCallback messageCallback_;
  WriteCompleteCallback writeCallback_;
};
#endif
