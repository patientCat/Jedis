#ifndef __TIMESTAMP_HH__
#define __TIMESTAMP_HH__

#include <chrono>
#include <exception>
#include <stdexcept>
#include <ctime>

// 首先要明白time_point 和 duration的区别
// 详情请查看cppreference

// time_point只能之间只能相减
// time_point 和duration之间既可以加也可以减
class Timestamp
{
  public:

      static const int64_t k_Milliseconds_Per_Seconds = 1000;
  static const int64_t k_Microseconds_Per_Seconds = 1000 * 1000;
  static const int64_t k_Microseconds_Per_Milliseconds = 1000;
  static const int64_t k_Nanoseconds_Per_Milliseconds = 1000 * 1000;

  using ClockType = std::chrono::system_clock;
  using Seconds = std::chrono::seconds ;
  using Milliseconds = std::chrono::milliseconds ;
  using CurrDurationType = Milliseconds ;
public:
  explicit Timestamp() = default;
  explicit Timestamp(const CurrDurationType &ms)
  : curr_time_point_(ms)
  {

  }

  bool operator < (const Timestamp &ts)
  {
    return curr_time_point_ < ts.curr_time_point_;
  }

  Timestamp & operator+=(const Seconds & s)
  {
    curr_time_point_ += s;
    return *this;
  }
  Timestamp & operator+=(const Milliseconds &ms)
  {
    curr_time_point_ += ms;
    return *this;
  }

  Timestamp & operator+(const Seconds & ts)
  {
    return (*this)+=ts;
  }

  Timestamp & operator+(const Milliseconds & ts)
  {
    return (*this)+=ts;
  }

  Timestamp & operator-=(const Seconds & s)
  {
    curr_time_point_ -= s;
    return *this;
  }
  Timestamp & operator-=(const Milliseconds & s)
  {
    curr_time_point_ -= s;
    return *this;
  }

  Timestamp & operator-(const Seconds & ts)
  {
    return (*this)-=ts;
  }

  Timestamp & operator-(const Milliseconds & ts)
  {
    return (*this)-=ts;
  }

  Milliseconds operator-(const Timestamp& ts)
  {
    if(curr_time_point_ < ts.curr_time_point_)
      throw std::logic_error("当前时间点小于后面时间点");
    return curr_time_point_ - ts.curr_time_point_;
  }
  

  int64_t since_epoch_milliseconds_count()const
  { 
    return curr_time_point_.time_since_epoch().count();
  }
  static Timestamp now(){
    return Timestamp(std::chrono::duration_cast<CurrDurationType>(std::chrono::system_clock::now().time_since_epoch()));
  }

  struct timespec to_timespect()
  {
    struct timespec ts;
    // 将整除部分给sec
    ts.tv_sec = curr_time_point_.time_since_epoch().count() / k_Milliseconds_Per_Seconds;
    // 将余数部分给nsec
    ts.tv_nsec = (curr_time_point_.time_since_epoch().count() % k_Milliseconds_Per_Seconds) *  k_Nanoseconds_Per_Milliseconds;
    return ts;
  }
  std::string to_string()
  {
    struct timespec ts = to_timespect();
    char buff[50] = {0};
    std::strftime(buff, sizeof buff, "%T", std::gmtime(&ts.tv_sec));
    char output[100] = {0};
    sprintf(output, "%s.%09ld", buff, ts.tv_nsec / k_Nanoseconds_Per_Milliseconds);
    return output;
  }
private:
  // 记录的时间点
  std::chrono::time_point<ClockType, CurrDurationType> curr_time_point_;
};

#endif

