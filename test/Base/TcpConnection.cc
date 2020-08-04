//c++ program
//design by >^.^<
//@date    2019-12-14 06:16:00
#include "TcpConnection.hh"
#include "Logging.hh"
#include "Reactor.hh"
#include <memory>


namespace{
  void default_connection_callback(const TcpConnectionPtr &conn)
  {
    if(conn->is_connected())
    {
      LOG_INFO << conn->sockAddr().to_string() << " is connected";
    }
    if(conn->is_disconnected())
    {
      LOG_INFO << conn->sockAddr().to_string() << " is disconnected";
    }
  }
}
TcpConnection::TcpConnection(Reactor* loop, int fd, const SocketAddr& addr)
    : loop_(loop)
    , sock_(fd)
    , addr_(addr)
    , fileEvent_(SocketEvent::new_event_handler(loop, fd))
  {
      fileEvent_->set_read_callback(std::bind(&TcpConnection::handle_read, this, std::placeholders::_1));
      fileEvent_->set_write_callback(std::bind(&TcpConnection::handle_write, this));
      fileEvent_->enable_read();
      onConnectionCallback_ = default_connection_callback;
  }

  void 
TcpConnection::handle_read(Timestamp recvTimePoint)
{
  int errNum;
  int n = readBuffer_.readv_from(sock_.fd(), &errNum);
  if(n > 0)
  {
    if(onMessageCallback_)
      onMessageCallback_(shared_from_this(), &readBuffer_, recvTimePoint);
  }
  else if(n == 0)
  {
    LOG_TRACE << addr_.to_string() << " client start disconnected" ;
    handle_close();
    // 断开
  }
  else{ // 出错
    handle_error(errNum);
  }
}

  void
TcpConnection::handle_write()
{
  int n = Socket::write(sock_.fd(), writeBuffer_.read_index_ptr(), writeBuffer_.readable_size());

  if(n > 0)
  {
    writeBuffer_.retrieve(n);
    // 如果写完了
    if(writeBuffer_.readable_size() == 0)
    {
      fileEvent_->disable_write();
      if(onWriteCompleteCallback_)
        onWriteCompleteCallback_(shared_from_this());
    }
  }
  else{
    handle_error(n);
  }
}

// 对于Send来说，是比较复杂的，但是当前我们就按照最简单的方式处理
// 版本1
// void 
// TcpConnection::send(const char *data, int len)
// {
//   int n = write(sock_.fd(), data, len);
// }

// 版本2
  void 
TcpConnection::send(const char *data, int len)
{
  if(!fileEvent_->is_enable_write())
  {
    int n = Socket::write(sock_.fd(), data, len);

    // 如果没有发送完毕，就需要注册一个写函数去去处理
    if(n < len)
    {
      writeBuffer_.append(data + n, len - n);
      fileEvent_->enable_write();
    }
  }
  else{
    writeBuffer_.append(data, len);
  }
}



void TcpConnection::connection_destroyed()
{
  // 单线程实际上不需要使用这个 
  // LOG_TRACE << addr_.to_string() << "多线程 TcpConnectionPtr 安全析构";
  // 让TcpConnection自动析构
}

// 被动断开
// 此时即使recvBuffer有该fd残留的数据也不要了。
// 此时即使writeBuffer还有数据要发给对方也不要了，因为对方已经断开了。这些数据没有意义了
  void 
TcpConnection::handle_close()
{
  fileEvent_->disable_all();
  loop_->remove_event(fileEvent_.get());

  assert(status_ == ConnectionStatus::kConnected);

  status_ = ConnectionStatus::kDisconnected;

  set_status(ConnectionStatus::kDisconnected);
  auto guard_from_this = shared_from_this();
  if(onConnectionCallback_)
    onConnectionCallback_(guard_from_this);

  // 让TcpServer把持有的连接删了
  
  onCloseCallback_(guard_from_this);
  LOG_TRACE << guard_from_this.use_count() ;
}
