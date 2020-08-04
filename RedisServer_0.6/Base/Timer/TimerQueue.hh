//
// Created by Pawn on 2020/8/2.
//

#ifndef JEDIS_TIMERQUEUE_HH
#define JEDIS_TIMERQUEUE_HH

#include "../Noncopyable.hh"
#include "../Event.hh"
#include "Timer.hh"
#include <queue>

class Reactor;
// 使用小根堆

class TimerPtrCmp
{
public:
  bool operator() (const TimerPtr &x1, const TimerPtr &x2)
  {
    // 到期时间越小优先级越高
    return x1->get_expire_time() < x2->get_expire_time();
  }
};

class TimerQueue {
public:
  TimerQueue(Reactor *r);
  ~TimerQueue();

  void add_timer(const TimerPtr & timer);
  void add_timer(const TimerCallback &cb, Timestamp when);
  void add_timer(const TimerCallback &cb, Timestamp when, Timestamp::Milliseconds interval);

private:
  void handle_expire();
  Reactor *reactor_;
  int timerfd_;
  SocketEvent socket_event_;
  std::priority_queue<TimerPtr, std::vector<TimerPtr>, TimerPtrCmp> timer_queue_;
};

#endif // JEDIS_TIMERQUEUE_HH
