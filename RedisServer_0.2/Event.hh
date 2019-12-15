#ifndef __EVENT_HH__
#define __EVENT_HH__

#include <boost/noncopyable.hpp>
#include <functional>
#include <memory>

#define AE_NONE       0 
#define AE_READABLE   1 
#define AE_WRITABLE   2

class EventLoop;

class FileEvent;
using FileEventPtr = std::shared_ptr<FileEvent>;

class FileEvent 
: boost::noncopyable
, public std::enable_shared_from_this<FileEvent>

{
  friend class EventLoop;
  using Callback = std::function<void(int)>;
public:
  FileEvent(EventLoop *loop, int fd);

  void RegisterReadHandler(Callback cb);
  void RegisterWriteHandler(Callback cb);

  void EnableReading();
  void EnableWriting();

  bool IsReading()
  {
    return mask_ & AE_READABLE;
  }

  bool IsWriting()
  {
    return mask_ & AE_WRITABLE;
  }

  void DisableReading();

  void DisableWriting();

private:
  void HandleRead(int fd)
  {
    if(readHandler_)
      readHandler_(fd);
  }
  void HandleWrite(int fd)
  {
    if(writeHandler_)
      writeHandler_(fd);
  }

  int FD() const { return fd_; }
  // 返回就绪的事件mask
  int Mask() const { return mask_; }
  int RMask() const { return rmask_; }
private:
  const int fd_;
  int mask_;
  int rmask_;
  Callback readHandler_;
  Callback writeHandler_;
  EventLoop *loop_;
};

struct FiredEvent
{
  FiredEvent() = default;
  FiredEvent(int fd, int rmask)
    : fd_(fd)
    , rmask_(rmask)
  {}

  int fd_;
  int rmask_;
};

class TimeEvent
{
};


#endif
