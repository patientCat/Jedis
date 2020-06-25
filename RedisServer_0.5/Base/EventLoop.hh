#ifndef __EVENTLOOP_HH__
#define __EVENTLOOP_HH__

#include "Event.hh"
#include "Poller.hh"
#include "Logging.hh"
#include "TcpConnection.hh"

#include <boost/noncopyable.hpp>
#include <vector>
#include <list>
#include <memory>
#include <chrono>

#include <sys/eventfd.h>


class FileEvent;
class TimeEvent;

class EventLoop : boost::noncopyable
{
  friend class FileEvent;
public:
  using TaskType = std::function<void()>;
  EventLoop()
    : maxfd_(10)
    // 我希望将wakupFd注册进去，当我想要主动唤醒poll的时候使用
    , wakeupEvent_(new FileEvent(this, eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC)))
    , setsize_(1024)
    , isStarting_(false)
    , fileEvents_(setsize_)
    , firedEvents_(setsize_)
    , poller_(new Poller())
  {
    wakeupEvent_->RegisterReadHandler(std::bind(&EventLoop::handleWakup, this));
  }
  ~EventLoop() = default;

  void Exit()
  {
    isStarting_ = false;
  }

  void Loop();
  void RunAfterPoll(TaskType && task);
private:
  void RegisterFileEvent(std::shared_ptr<FileEvent> fileEventPtr);
  void DeleteFileEvent(int fd);
  void RegisterTimeEvent();
  void DeleteTimeEvent();
  void doTrivalThings();
  void handleWakup()
  {
    uint64_t one;
    read(wakeupEvent_->FD(),  &one, sizeof(one));
    LOG_DEBUG << "主动wake up";
  }
  void notifyEvent()
  {
    uint64_t one = 1;
    write(wakeupEvent_->FD(), &one, sizeof(one));
  }

  int maxfd_;
  FileEventPtr wakeupEvent_;
  int setsize_;
  bool isStarting_;

  std::vector<std::shared_ptr<FileEvent>> fileEvents_;
  std::vector<FiredEvent> firedEvents_;
  std::list<TimeEvent> timeEvents_;
  std::unique_ptr<Poller> poller_;

  std::list<TaskType> taskList_;
};
#endif


