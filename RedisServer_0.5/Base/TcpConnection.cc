//c++ program
//design by >^.^<
//@date    2019-12-14 06:16:00
#include "TcpConnection.hh"
#include "Logging.hh"
#include "EventLoop.hh"

void 
TcpConnection::handleRead(Timestamp recvTimePoint)
{
  int errNum;
  int n = readBuffer_.readFd(sock_.FD(), &errNum);
  if(n > 0)
  {
    if(onMessageCallback_)
      onMessageCallback_(shared_from_this(), &readBuffer_, recvTimePoint);
  }
  else if(n == 0)
  {
    LOG_TRACE << addr_.ToString() << " client start disconnected" ;
    handleClose();
    // 断开
  }
  else{ // 出错
  }
}

void
TcpConnection::handleWrite()
{
  int n = write(sock_.FD(), writeBuffer_.readIndexPtr(), writeBuffer_.readableSize()); 

  if(n > 0)
  {
    writeBuffer_.updateReadIndex(n);
    // 如果写完了
    if(writeBuffer_.readableSize() == 0)
    {
      fileEvent_->DisableWriting();
      if(onWriteCompleteCallback_)
        onWriteCompleteCallback_(shared_from_this());
    }
  }
  else{
    // 注意要关闭SIG_PIPE信号
    if(n == 0)
      handleClose();
    
  }
}

// 对于Send来说，是比较复杂的，但是当前我们就按照最简单的方式处理
// 版本1
// void 
// TcpConnection::Send(const char *data, int len)
// {
//   int n = write(sock_.FD(), data, len);
// }

// 版本2
void 
TcpConnection::Send(const char *data, int len)
{
  if(!fileEvent_->IsWriting())
  {
    int n = write(sock_.FD(), data, len);

    // 如果没有发送完毕，就需要注册一个写函数去去处理
    if(n < len)
    {
      writeBuffer_.append(data + n, len - n);
      fileEvent_->EnableWriting();
    }
  }
  else{
      writeBuffer_.append(data, len);
  }
}

void TcpConnection::connectionDestroyed()
{
  LOG_TRACE <<  addr_.ToString() << " real disconnected ";
  fileEvent_->DisableAll();
  // socket 自动析构关闭
}

void 
TcpConnection::handleClose()
{
  fileEvent_->DisableReading();

  LOG_TRACE << addr_.ToString() << " close reading ";
  setStatus(ConnectionStatus::kDisconnected);
  auto guard_from_this = shared_from_this();
  onConnectionCallback_(guard_from_this);
  onCloseCallback_(guard_from_this);
}
