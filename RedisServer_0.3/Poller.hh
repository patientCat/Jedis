#ifndef __POLLER_HH__
#define __POLLER_HH__

#include <boost/noncopyable.hpp>
#include <memory>
#include <vector>
#include "Event.hh"

using std::vector;

class Poller : boost::noncopyable
{
public:
  Poller();
  ~Poller();

  // 根据mask，来决定关注读或者写事件
  bool UpdateEvent(int fd, int mask, bool isRegistered);
  bool DeleteEvent(int fd);
  void Poll(int count, int setsize, vector<FiredEvent>* firedEvents);
private:
  int epfd_;
};
#endif
