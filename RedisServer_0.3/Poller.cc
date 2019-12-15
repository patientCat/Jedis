//c++ program
//design by >^.^<
//@date    2019-12-01 04:52:12
#include "Poller.hh"
#include "Event.hh"

#include <string.h>
#include <sys/epoll.h>

Poller::Poller()
  : epfd_(epoll_create(EPOLL_CLOEXEC))
{
}

Poller::~Poller()
{
  ::close(epfd_);
}

bool 
Poller::UpdateEvent(int fd, int mask, bool isRegistered)
{
  struct epoll_event ee;
  bzero(&ee, sizeof(ee));

  if(mask & AE_READABLE)
  {
    ee.events |= EPOLLIN;
  }
  if(mask & AE_WRITABLE)
  {
    ee.events |= EPOLLOUT;
  }
  ee.data.fd = fd;
  
  // 对于一个事件来说，如果有返回了读事件或者写事件，那么其之前就已经被注册进去了。
  // 否则的话其rmask应该是AE_NONE的
  int op = isRegistered == false ? EPOLL_CTL_ADD : EPOLL_CTL_MOD;

  if(epoll_ctl(epfd_, op, fd, &ee) == -1) 
  {
    return -1;
  }
  return 0;
}

// 删除epfd关注的事件
bool 
Poller::DeleteEvent(int fd)
{
  if(epoll_ctl(epfd_, EPOLL_CTL_DEL, fd, NULL) == -1)
  {
    return -1;
  }
  return 0;
}

void 
Poller::Poll(int count, int setsize, vector<FiredEvent>* activeEvents)
{
  int retval = 0;
  struct epoll_event events[setsize];

  retval = epoll_wait(epfd_, events, setsize, count);

  if(retval > 0)
  {
    int j;
    int numevents = retval;
    activeEvents->resize(numevents);

    for(j = 0; j < numevents; j++)
    {
      int mask = 0;
      struct epoll_event * e = events + j;
      if(e->events & EPOLLIN) mask |= AE_READABLE;
      if(e->events & EPOLLOUT) mask |= AE_WRITABLE;
      if(e->events & EPOLLERR) mask |= AE_WRITABLE;
      if(e->events & EPOLLHUP) mask |= AE_WRITABLE;

      activeEvents->push_back(FiredEvent {e->data.fd, mask});
    }
  }
}

