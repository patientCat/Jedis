//c++ program
//design by >^.^<
//@date    2019-12-14 06:16:00
#include "TcpConnection.hh"
#include "Logging.hh"

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
    LOG_INFO << "[" << addr_.ToString() << "] client is connected" ;
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
