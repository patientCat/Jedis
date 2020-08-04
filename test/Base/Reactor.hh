#ifndef __EVENTLOOP_HH__
#define __EVENTLOOP_HH__

#include "Event.hh"
#include "Poller.hh"
#include "Logging.hh"
#include "TcpConnection.hh"
#include "Socket.hh"
#include "Noncopyable.hh"
#include "Timestamp.hh"
#include "Timer/TimerQueue.hh"


#include <vector>
#include <list>
#include <memory>
#include <chrono>




#include <sys/eventfd.h>


class SocketEvent;
class TimeEvent;
class TimerQueue;



// Reactor 一定要管理好SocketEvent
// Reactor没有持有SocketEvent。直接将其注册到Epoll中，wait返回时候，回调即可
// 因此当SocketEvent关闭的时候，直接调用remove_event就可以了
class Reactor : Noncopyable
{
  friend class SocketEvent;
public:
  using TaskType = std::function<void()>;
  Reactor();

  ~Reactor() = default;

  void exit()
  { is_starting_ = false;
  }

  void loop();
  // 唤醒epoll，然后去执行task
  void run_in_loop(TaskType && task);
  // 这里并不是立即执行，而是将其排到loop的队列中，当某次事件就绪后，会连带着一起做了。
  void queue_in_loop(TaskType && task);
  // 定时事件
  void run_after(TaskType task, const Timestamp::Milliseconds &ms);
  void run_every(TaskType task, const Timestamp::Milliseconds &interval);

  void update_event(SocketEvent* socket_event_ptr);
  void remove_event(SocketEvent* socket_event_ptr);
private:
  // 添加，或者修改事件
  void add_time_event();
  void delete_time_event();
  void do_trival_things();

  // epoll_wait error的情况
  void handle_error()
  {
    // 还没想好怎么做
    LOG_ERROR << "epoll_wait_err";
  }
  void handle_weak_up()
  {
    uint64_t one;
    Socket::read(wakeupEvent_->fd(),  &one, sizeof(one));
    LOG_DEBUG << "主动wake up";
  }
  // 唤醒event_fd
  void wake_up()
  {
    uint64_t one = 1;
    Socket::write(wakeupEvent_->fd(), &one, sizeof(one));
  }

  std::unique_ptr<SocketEvent> wakeupEvent_;
  bool is_starting_{false};

  std::vector<SocketEvent*> active_socket_event_list_;
  std::list<TimeEvent> timeEvents_;
  std::list<TaskType> taskList_;
  std::unique_ptr<Poller> poller_;
  std::unique_ptr<TimerQueue> timer_queue_;
};
#endif


