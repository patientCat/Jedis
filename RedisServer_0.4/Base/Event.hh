#ifndef __EVENT_HH__
#define __EVENT_HH__

#include "Timestamp.hh"

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
  using ReadCallback = std::function<void(Timestamp)>;
  using WriteCallback = std::function<void()>;
protected:
  FileEvent(EventLoop *loop, int fd);
public:
  static FileEventPtr NewFileEvent(EventLoop *loop, int fd)
  {
    FileEventPtr ptr(new FileEvent(loop, fd));
    return ptr;
  }

  void RegisterReadHandler(ReadCallback cb);
  void RegisterWriteHandler(WriteCallback cb);

  void EnableReading();
  void EnableWriting();
  void DisableReading();
  void DisableWriting();

  bool IsReading()
  {
    return mask_ & AE_READABLE;
  }
  bool IsWriting()
  {
    return mask_ & AE_WRITABLE;
  }

private:
  void HandleRead(const Timestamp& recvTime)
  {
    if(readHandler_)
      readHandler_(recvTime);
  }
  void HandleWrite()
  {
    if(writeHandler_)
      writeHandler_();
  }

  int FD() const { return fd_; }
  // 返回就绪的事件mask
  int Mask() const { return mask_; }
  int RMask() const { return rmask_; }
private:
  const int fd_;
  int mask_;
  int rmask_;
  bool isRegistered_;
  ReadCallback readHandler_;
  WriteCallback writeHandler_;
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
