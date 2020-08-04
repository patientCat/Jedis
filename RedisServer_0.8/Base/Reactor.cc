//c++ program
//design by >^.^<
//@date    2019-12-01 06:22:50
#include "Reactor.hh"
#include "Event.hh"
#include "Poller.hh"
#include "Timestamp.hh"
#include "Logging.hh"
#include <iostream>
#include "Timer/TimerQueue.hh"

using std::shared_ptr;
using std::chrono::milliseconds;
using std::cin;
using std::cout;
using std::endl;


Reactor::Reactor()
// 我希望将wakupFd注册进去，当我想要主动唤醒poll的时候使用
    : wakeupEvent_(std::make_unique<SocketEvent>(this, eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC)))
    , is_starting_(false)
    , poller_(new Poller())
    , timer_queue_(std::make_unique<TimerQueue>(this))
{
  wakeupEvent_->set_read_callback(std::bind(&Reactor::handle_weak_up, this));
}

// 添加事件
void 
Reactor::update_event(SocketEvent* socket_event_ptr)
{
  if(!socket_event_ptr)
    LOG_ERROR << "update_event err, socket_event not exist";

  // 如果已经注册，那么添加事件
  if(socket_event_ptr->isRegistered_)
  {
    poller_->mod_event(socket_event_ptr);
    LOG_DEBUG << "更新事件成功";
  }else{ // 否则，修改
    poller_->add_event(socket_event_ptr);
    LOG_DEBUG << "添加事件成功";
  }

  // 标记事件已经注册
  if(!socket_event_ptr->isRegistered_)
  {
    socket_event_ptr->isRegistered_ = true;
  }
}

void 
Reactor::remove_event(SocketEvent* socket_event_ptr)
{
    poller_->remove_event(socket_event_ptr);
    LOG_DEBUG << "删除事件成功";
}

void 
Reactor::loop()
{
  is_starting_ = true;
  while(is_starting_)
  {
    active_socket_event_list_.clear();
    poller_->poll(active_socket_event_list_);
    Timestamp recvTime = Timestamp::now();
    for(SocketEvent* event_ptr : active_socket_event_list_)
    {
      if(event_ptr->revent_mask() & EVENT_TYPE_READABLE)
      {
        event_ptr->handle_read(recvTime);
      }
      if(event_ptr->revent_mask() & EVENT_TYPE_WRITABLE)
      {
        event_ptr->handle_write();
      }
      if(event_ptr->revent_mask() & EVENT_TYPE_EPOLL_ERR)
      {
        handle_error();
      }
    }

      do_trival_things();
  }
}
  
void 
Reactor::run_in_loop(TaskType && task)
{
  if(1)
  {// 如果在Reactor所属的线程, 当点Reactor是单线程，所以一直是true
    task();
  }else{
    // 后序多线程
    queue_in_loop(std::move(task));
    // 2. 唤醒Poll
    wake_up();
  }
}

void
Reactor::queue_in_loop(TaskType &&task) {
  taskList_.push_back(std::move(task));
}


void Reactor::run_after(TaskType task, const Timestamp::Milliseconds &ms) {
  timer_queue_->add_timer(task, Timestamp::now() + ms);
}


void Reactor::run_every(TaskType task, const Timestamp::Milliseconds &interval) {
  timer_queue_->add_timer(task, Timestamp::now() + interval, interval);
}

void
Reactor::do_trival_things()
{
  for(auto task : taskList_)
  {
    task();
  }
  taskList_.clear();
}
