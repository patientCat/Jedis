#pragma once


#include "../Timestamp.hh"
#include "../Callback.hh"

class Timer
{
public:
  Timer(const TimerCallback& cb, Timestamp when)
      : cb_(cb)
      , expire_time_(when)
  {
  }

  void set_persist(Timestamp::Milliseconds interval)
  {
    LOG_ERROR_IF(interval.count() > 0, "interval 必须大于0");
    is_persist_ = true;
    interval_ = interval;
  }

  void handle() { cb_(); }
  void reset_expire_time(const Timestamp& ts)
  {
    expire_time_ = ts;
  }
  [[nodiscard]] bool is_persist() const { return is_persist_; }
  [[nodiscard]] Timestamp::Milliseconds get_interval() const { return interval_; }
  [[nodiscard]] Timestamp get_expire_time() const { return expire_time_; }
private:
  TimerCallback cb_;
  Timestamp expire_time_;
  bool is_persist_{false};
  Timestamp::Milliseconds interval_;
};

using TimerPtr = std::shared_ptr<Timer>;