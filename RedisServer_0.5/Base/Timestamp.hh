#ifndef __TIMESTAMP_HH__
#define __TIMESTAMP_HH__

#include <chrono>


using std::chrono::milliseconds;
class Timestamp
{
public:
  static const long kMicroSecondsPerSecond = 1e6;
  explicit Timestamp() = default;
  explicit Timestamp(const milliseconds &ms)
    : epochMilliseconds_(ms)
  {
  }
  Timestamp & operator+=(const Timestamp& ts)
  {
    this->epochMilliseconds_ += ts.epochMilliseconds_;
    return *this;
  }
  Timestamp & operator+(const Timestamp& ts)
  {
    return (*this)+=ts;
  }
  Timestamp & operator-=(const Timestamp& ts)
  {
    this->epochMilliseconds_ -= ts.epochMilliseconds_;
    return *this;
  }
  Timestamp & operator-(const Timestamp& ts)
  {
    return (*this)-=ts;
  }
  

  std::chrono::milliseconds Milliseconds()const 
  { 
    return epochMilliseconds_;
  }
  static Timestamp Now(){
    return Timestamp(std::chrono::duration_cast<milliseconds>(std::chrono::system_clock::now().time_since_epoch()));
  }
private:
  std::chrono::milliseconds epochMilliseconds_;
};

#endif
