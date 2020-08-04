//c++ program
//design by >^.^<
//@date    2020-08-02 02:42:46
#include <iostream>

#include <sys/epoll.h>
#include "RealTimer.hh"


using namespace std;
int main()
{
  int timerfd = RealTimer::create_timerfd();
  Timestamp curr = Timestamp::now();
  cout << curr.to_string() << endl;
  RealTimer::reset_timerfd(timerfd, curr+ Timestamp::CurrDurationType{5000});

  
  int epfd = epoll_create1(EPOLL_CLOEXEC);
  struct epoll_event ee;
  ee.data.fd = timerfd;
  ee.events = EPOLLIN;
  epoll_ctl(epfd, EPOLL_CTL_ADD, timerfd, &ee);

  epoll_wait(epfd, &ee, 1, -1);
  RealTimer::read_timerfd(timerfd, Timestamp::now());
  cout << Timestamp::now().to_string() << endl;
}
