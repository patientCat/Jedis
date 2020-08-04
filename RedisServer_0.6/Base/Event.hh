#ifndef __EVENT_HH__
#define __EVENT_HH__

#include "Timestamp.hh"
#include "Noncopyable.hh"
#include "Logging.hh"
#include "Copyable.hh"

#include <functional>
#include <memory>

#define EVENT_TYPE_NONE       0
#define EVENT_TYPE_READABLE   1
#define EVENT_TYPE_WRITABLE   2
#define EVENT_TYPE_EPOLL_ERR   4

class Reactor;

class SocketEvent;
using SocketEventSharedPtr = std::shared_ptr<SocketEvent>;

class SocketEvent
: Noncopyable
{
  friend class Reactor;
  friend class Poller;
  using ReadCallback = std::function<void(Timestamp)>;
  using WriteCallback = std::function<void()>;
protected:
public:
  SocketEvent(Reactor *loop, int fd);
  static  SocketEventSharedPtr new_event_handler(Reactor *loop, int fd)
  {
    SocketEventSharedPtr ptr(new SocketEvent(loop, fd));
    return ptr;
  }

  void set_read_callback(ReadCallback cb);
  void set_write_callback(WriteCallback cb);

  void enable_read();
  void enable_write();
  void disable_read();
  void disable_write();
  void disable_all();

  bool is_enable_read() const
  {
    return mask_ & EVENT_TYPE_READABLE;
  }
  bool is_enable_write() const
  {
    return mask_ & EVENT_TYPE_WRITABLE;
  }

private:
  void handle_read(const Timestamp& recvTime)
  {
    if(readHandler_)
      readHandler_(recvTime);
    else
        LOG_ERROR << "code err: 没有设置read_callback，却handle_read，请设置read_callback";
  }
  void handle_write()
  {
    if(writeHandler_)
      writeHandler_();
    else
      LOG_ERROR << "code err: 没有设置write_callback，却handle_write，请设置write_callback";
  }

  int fd() const { return fd_; }
  // 关注的事件类型
  int event_mask() const { return mask_; }
  // 返回就绪的事件mask
  void set_rmask(int rmask) { rmask_ = rmask;  };
  int revent_mask() const { return rmask_; }
private:
  const int fd_;
  int mask_;
  int rmask_;
  bool isRegistered_;
  ReadCallback readHandler_;
  WriteCallback writeHandler_;
  Reactor *loop_;
};

// 就绪事件
class FiredEvent : Copyable
{
    FiredEvent() = default;
  FiredEvent(int fd, int rmask)
    : fd_(fd)
    , rmask_(rmask)
  {}

public:
  int fd() const
  {
      return fd_;
  }
  int rmask() const
  {
      return rmask_;
  }

private:
  int fd_;
  int rmask_;
};

class TimeEvent : Noncopyable
{
};


#endif
