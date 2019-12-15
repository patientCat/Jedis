//c++ program
//design by >^.^<
//@date    2019-12-01 05:37:18
#include "Event.hh"
#include "EventLoop.hh"

FileEvent::FileEvent(EventLoop *loop, int fd)
  : fd_(fd)
  , mask_(AE_NONE)
  , rmask_(AE_NONE)
  , loop_(loop)
{}

void 
FileEvent::RegisterReadHandler(Callback cb)
{
  readHandler_ = cb;
}

void 
FileEvent::RegisterWriteHandler(Callback cb)
{
  writeHandler_ = cb;
}

void 
FileEvent::EnableReading()
{
  mask_ = mask_ | AE_READABLE;
  loop_->RegisterFileEvent(shared_from_this());
}

void 
FileEvent::EnableWriting()
{
  mask_ = mask_ | AE_WRITABLE;
  loop_->RegisterFileEvent(shared_from_this());
}
void 
FileEvent::DisableReading()
{
  mask_ = mask_ & (!AE_READABLE);
}

void 
FileEvent::DisableWriting()
{
  mask_ = mask & (!AE_WRITABLE);
}

