//c++ program
//design by >^.^<
//@date    2019-12-01 04:52:12
#include "Poller.hh"
#include "Event.hh"

#include "Logging.hh"
#include <unistd.h>
#include <string.h>

Poller::Poller()
  : epfd_(epoll_create(EPOLL_CLOEXEC))
  , revents_vec_(1024)
{
}

Poller::~Poller()
{
  ::close(epfd_);
}

// EPOLL 关注 fd
void
Poller::add_event(SocketEvent* socket_event_ptr) {

   event_size_++;
   if(event_size_ > revents_vec_.size())
     revents_vec_.resize(2 * event_size_);
   struct epoll_event ee;
   bzero(&ee, sizeof(ee));

   int mask = socket_event_ptr->event_mask();
   int fd = socket_event_ptr->fd();
   if(mask & EVENT_TYPE_READABLE)
   {
       ee.events |= EPOLLIN;
   }
    if(mask & EVENT_TYPE_WRITABLE) {
        ee.events |= EPOLLOUT;
    }

  ee.data.ptr = reinterpret_cast<void*>(socket_event_ptr);

    if(epoll_ctl(epfd_, EPOLL_CTL_ADD, fd, &ee) < 0)
    {
        LOG_SYSERR << "EPOLL_CTL_ADD err";
    }
}
void
Poller::mod_event(SocketEvent* socket_event_ptr)
{
  struct epoll_event ee;
  bzero(&ee, sizeof(ee));

  int mask = socket_event_ptr->event_mask();
  int fd = socket_event_ptr->fd();
  if(mask & EVENT_TYPE_READABLE)
  {
    ee.events |= EPOLLIN;
  }
  if(mask & EVENT_TYPE_WRITABLE)
  {
    ee.events |= EPOLLOUT;
  }
  ee.data.ptr = reinterpret_cast<void*>(socket_event_ptr);

  if(epoll_ctl(epfd_, EPOLL_CTL_MOD, fd, &ee) < 0)
  {
      LOG_SYSERR << "EPOLL_CTL_MOD err";
  }
}

// 删除epfd关注的事件
void 
Poller::remove_event(SocketEvent *socket_event_ptr)
{
  event_size_--;
  int fd = socket_event_ptr->fd();
  if(epoll_ctl(epfd_, EPOLL_CTL_DEL, fd, NULL) < 0)
  {
    LOG_SYSERR << "EPOLL_CTL_DEL err";
  }
}

// 返回就绪的事件
void 
Poller::poll(vector<SocketEvent*>& activeEvents, int time_out)
{
  int retval = 0;
  retval = epoll_wait(epfd_, revents_vec_.data(), event_size_, time_out);

  if(retval < 0)
  {
      LOG_ERROR << "EPOLL WAIT ERROR";
  }
  if(retval == 0)
  {
      LOG_TRACE << "nothing happened";
  }

  if(retval > 0)
  {
    int num_events = retval;
    LOG_TRACE << "ready " << num_events << "事件";

    for(int i = 0; i < num_events; i++)
    {
      int rmask = 0;
      struct epoll_event * e = &revents_vec_[i];
      if(e->events & EPOLLIN) rmask |= EVENT_TYPE_READABLE;
      if(e->events & EPOLLOUT) rmask |= EVENT_TYPE_WRITABLE;
      if(e->events & EPOLLERR) rmask |= EVENT_TYPE_EPOLL_ERR;
      if(e->events & EPOLLHUP) rmask |= EVENT_TYPE_EPOLL_ERR;

      SocketEvent *socket_event_ptr = reinterpret_cast<SocketEvent*>(e->data.ptr);
      socket_event_ptr->set_rmask(rmask);
      activeEvents.push_back(socket_event_ptr);
    }
  }

}

