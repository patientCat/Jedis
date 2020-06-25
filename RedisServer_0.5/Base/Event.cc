//c++ program
//design by >^.^<
//@date    2019-12-01 05:37:18
#include "Event.hh"
#include "EventLoop.hh"

FileEvent::FileEvent(EventLoop *loop, int fd)
  : fd_(fd)
  , mask_(AE_NONE)
  , rmask_(AE_NONE)
  , isRegistered_(false)
  , loop_(loop)
{}

void 
FileEvent::RegisterReadHandler(ReadCallback cb)
{
  readHandler_ = cb;
}

void 
FileEvent::RegisterWriteHandler(WriteCallback cb)
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
FileEvent::DisableAll()
{
  if(isRegistered_)
  {
    loop_->DeleteFileEvent(fd_);
  }
}

void
FileEvent::DisableReading()
{
  if(mask_ & AE_READABLE)
  {
    mask_ = mask_ & (!AE_READABLE);
    loop_->RegisterFileEvent(shared_from_this());
  }
}

void 
FileEvent::DisableWriting()
{
  if(mask_ & AE_WRITABLE)
  {
    mask_ = mask_ & (!AE_WRITABLE);
    loop_->RegisterFileEvent(shared_from_this());
  }
}
