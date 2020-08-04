#ifndef __POLLER_HH__
#define __POLLER_HH__

#include "Noncopyable.hh"
#include "Event.hh"

#include <memory>
#include <vector>

#include <sys/epoll.h>

using std::vector;

class SocketEvent;
class Poller : Noncopyable
{
public:
  Poller();
  ~Poller();

  // 根据mask，来决定关注读或者写事件
  void add_event(SocketEvent* socket_event_ptr);
  void mod_event(SocketEvent* socket_event_ptr);
  void remove_event(SocketEvent* socket_event_ptr);
  void poll(vector<SocketEvent*>& activeEvents, int time_out = -1);

private:
  int epfd_;
  int event_size_;
  std::vector<epoll_event> revents_vec_;
};
#endif
