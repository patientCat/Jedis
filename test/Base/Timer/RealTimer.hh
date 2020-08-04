#pragma once
#include <sys/timerfd.h>
#include "../Timestamp.hh"
//#include "../Logging.hh"

#include <string.h>
#include <unistd.h>

#include <chrono>

// timerfd簇函数的定时器

using namespace std;

class RealTimer
{

  RealTimer() = delete;
  ~RealTimer() = delete;
  public:
  // 创建定时器
  static int create_timerfd(bool is_real_timer = false)
  {
    int clock_id = is_real_timer ? CLOCK_REALTIME : CLOCK_MONOTONIC;
    int timerfd = timerfd_create(clock_id, TFD_NONBLOCK | TFD_CLOEXEC);
    if(timerfd < 0)
    {
    //  LOG_SYSERR << "timerfd_create failed"; 
    }
    return timerfd;
  }


  // 计算俩个时间点的duration然后转为timespec
  static struct timespec how_much_time_from_now(Timestamp when) // 做了Timestamp到timespec的转换，但精度没有那么高
  {
    Timestamp::Milliseconds time_duration = when - Timestamp::now();
    int64_t ms = time_duration.count();
    struct timespec ts;
    ts.tv_sec = static_cast<time_t>(
        ms / 1000);
    ts.tv_nsec = static_cast<int64_t>(
        (ms % 1000) * 1000 * 1000);
    return ts;
  }

  // 读取定时器事件
  static void read_timerfd(int timerfd, Timestamp now)
  {
    uint64_t howmany;
    ssize_t n = ::read(timerfd, &howmany, sizeof howmany);
   // LOG_TRACE << "TimerQueue::handleRead() " << howmany << "at " << now.to_string();
    if (n != sizeof howmany)
    {
    //  LOG_ERROR << "TimerQueue::handleRead() reads " << n << " bytes instead of 8";
    }
  }

  // 重置定时器超时时刻, 绝对时间
  static void reset_timerfd(int timerfd, Timestamp expiration)
  {
    // wake up loop by timerfd_settime()
    struct itimerspec newValue;
    struct itimerspec oldValue;
    memset(&newValue, 0, sizeof newValue);
    memset(&oldValue, 0, sizeof oldValue);

    newValue.it_value = how_much_time_from_now(expiration);
    int ret = ::timerfd_settime(timerfd, 0, &newValue, &oldValue);
    if (ret)
    {
//      LOG_SYSERR << "timerfd_settime()";
    }
  }
};

