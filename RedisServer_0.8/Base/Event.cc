//c++ program
//design by >^.^<
//@date    2019-12-01 05:37:18
#include "Event.hh"
#include "Reactor.hh"

SocketEvent::SocketEvent(Reactor *loop, int fd)
  : fd_(fd)
  , mask_(EVENT_TYPE_NONE)
  , rmask_(EVENT_TYPE_NONE)
  , isRegistered_(false)
  , loop_(loop)
{}

void 
SocketEvent::set_read_callback(ReadCallback cb)
{
  readHandler_ = cb;
}

void 
SocketEvent::set_write_callback(WriteCallback cb)
{
  writeHandler_ = cb;
}

void 
SocketEvent::enable_read()
{
  mask_ = mask_ | EVENT_TYPE_READABLE;
  loop_->update_event(this);
}

void 
SocketEvent::enable_write()
{
  mask_ = mask_ | EVENT_TYPE_WRITABLE;
  loop_->update_event(this);
}

void 
SocketEvent::disable_all()
{
  mask_ = EVENT_TYPE_NONE;
  if(isRegistered_)
  {
      loop_->update_event(this);
  }
}

void
SocketEvent::disable_read()
{
  if(mask_ & EVENT_TYPE_READABLE)
  {
    mask_ = mask_ & (!EVENT_TYPE_READABLE);
    loop_->update_event(this);
  }
}

void 
SocketEvent::disable_write()
{
  if(mask_ & EVENT_TYPE_WRITABLE)
  {
    mask_ = mask_ & (!EVENT_TYPE_WRITABLE);
    loop_->update_event(this);
  }
}
