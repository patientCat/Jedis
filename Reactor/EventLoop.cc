//c++ program
//design by >^.^<
//@date    2019-12-01 06:22:50
#include "EventLoop.hh"
#include "Event.hh"
#include "Poller.hh"
#include <iostream>

using std::shared_ptr;
using std::chrono::milliseconds;
using std::cin;
using std::cout;
using std::endl;

void 
EventLoop::RegisterFileEvent(shared_ptr<FileEvent> fileEventPtr)
{
  int fd = fileEventPtr->FD();
  if(fd > maxfd_)
    maxfd_ = fd;
  if(fd > setsize_)
  {
    setsize_ = fd * 2;
    fileEvents_.resize(setsize_);
  }

  fileEvents_[fd] = fileEventPtr;
  int ret = poller_->UpdateEvent(fd, fileEventPtr->Mask());
  if(ret != 0)
    cout << "注册事件失败" << endl;
  else
    cout << "注册事件成功" << endl;
}

void 
EventLoop::DeleteFileEvent(int fd)
{
  poller_->DeleteEvent(fd);
}

void 
EventLoop::Loop()
{
  isStarting_ = true;
  while(isStarting_)
  {
    poller_->Poll(-1, maxfd_, &firedEvents_);
    for(auto &one : firedEvents_)
    {
      if(one.rmask_ & AE_READABLE)
      {
        fileEvents_[one.fd_]->HandleRead(one.fd_);
      }
      if(one.rmask_ & AE_WRITABLE)
      {
        fileEvents_[one.fd_]->HandleWrite(one.fd_);
      }
    }
  }
}
  
void 
EventLoop::beforeWait()
{
}
