//
// Created by Pawn on 2020/8/2.
//

#include "TimerQueue.hh"
#include "RealTimer.hh"
#include "../Reactor.hh"

TimerQueue::TimerQueue(Reactor *r)
  : reactor_(r)
  , timerfd_(RealTimer::create_timerfd())
  , socket_event_(r, timerfd_)
{
    socket_event_.set_read_callback(std::bind(&TimerQueue::handle_expire, this));
    socket_event_.enable_read();
}

TimerQueue::~TimerQueue() {
    ::close(timerfd_);
}

// 添加定时器
void TimerQueue::add_timer(const TimerPtr &timer) {
  if(!timer_queue_.empty())
  {
    // 如果当前的timer比优先级队头时间还小
    if(timer->get_expire_time() < timer_queue_.top()->get_expire_time())
      // 更新RealTimer定时器时间
      RealTimer::read_timerfd(timerfd_, timer->get_expire_time());
  }
  timer_queue_.push(timer);
}

void TimerQueue::add_timer(const TimerCallback &cb, Timestamp when) {
  add_timer(std::make_shared<Timer>(cb, when)) ;
}

void TimerQueue::add_timer(const TimerCallback &cb, Timestamp when, Timestamp::Milliseconds interval) {
  auto timer = std::make_shared<Timer>(cb, when);
  timer->set_persist(interval);
  add_timer(timer);
}

// 定时器到时后，timerfd就会就绪。此时需要处理定时器callback
void TimerQueue::handle_expire() {
  auto now = Timestamp::now();
  RealTimer::read_timerfd(timerfd_, now);

  // 处理所有定时器
  while(true)
  {
    auto timer = timer_queue_.top();
    if(timer->get_expire_time() < now)
    {
      timer->handle();
      // 如果是永久的定时器
      if(timer->is_persist())
      {
        timer->reset_expire_time(now + timer->get_interval());
        timer_queue_.push(timer);
      }
      timer_queue_.pop();
    }else{
      break;
    }
  }

  // 重新设定定时器队列
  if(!timer_queue_.empty())
    RealTimer::read_timerfd(timerfd_, timer_queue_.top()->get_expire_time());
}