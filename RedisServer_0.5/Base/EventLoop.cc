//c++ program
//design by >^.^<
//@date    2019-12-01 06:22:50
#include "EventLoop.hh"
#include "Event.hh"
#include "Poller.hh"
#include "Timestamp.hh"
#include "Logging.hh"
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

  int ret = poller_->UpdateEvent(fd, fileEventPtr->Mask(), fileEventPtr->isRegistered_);
  if(ret != 0){
    LOG_DEBUG << "注册事件失败";
  }
  else{
    LOG_DEBUG << "注册事件成功";
  }

  if(!fileEventPtr->isRegistered_)
  {
    fileEvents_[fd] = fileEventPtr;
    fileEventPtr->isRegistered_ = true;
  }
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
    Timestamp recvTime = Timestamp::Now();
    for(auto &one : firedEvents_)
    {
      if(one.rmask_ & AE_READABLE)
      {
        fileEvents_[one.fd_]->HandleRead(recvTime);
      }
      if(one.rmask_ & AE_WRITABLE)
      {
        fileEvents_[one.fd_]->HandleWrite();
      }
    }

    doTrivalThings();
  }
}
  
void 
EventLoop::RunAfterPoll(TaskType && task)
{
  // 1. 先将需要处理的事件注册到任务队列去
  taskList_.emplace_back(std::move(task));
  // 2. 唤醒Poll
  notifyEvent();
}

void 
EventLoop::doTrivalThings()
{
  for(auto &task : taskList_)
  {
    task();
  }
  taskList_.clear();
}
