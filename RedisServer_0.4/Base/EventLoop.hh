#ifndef __EVENTLOOP_HH__
#define __EVENTLOOP_HH__

#include "Event.hh"
#include "Poller.hh"

#include <boost/noncopyable.hpp>
#include <vector>
#include <list>
#include <memory>
#include <chrono>


class FileEvent;
class TimeEvent;

class EventLoop : boost::noncopyable
{
  friend class FileEvent;
public:
  EventLoop()
    : maxfd_(10)
    , setsize_(1024)
    , isStarting_(false)
    , fileEvents_(setsize_)
    , firedEvents_(setsize_)
    , poller_(new Poller())
  {

  }
  ~EventLoop() = default;

  void Exit()
  {
    isStarting_ = false;
  }

  void Loop();
  void beforeWait();
private:
  void RegisterFileEvent(std::shared_ptr<FileEvent> fileEventPtr);
  void DeleteFileEvent(int fd);
  void RegisterTimeEvent();
  void DeleteTimeEvent();

  int maxfd_;
  int setsize_;
  bool isStarting_;

  std::vector<std::shared_ptr<FileEvent>> fileEvents_;
  std::vector<FiredEvent> firedEvents_;
  std::list<TimeEvent> timeEvents_;
  std::unique_ptr<Poller> poller_;
};
#endif


