//c++ program
//design by >^.^<
//@date    2019-12-01 05:37:18
#include "Event.hh"

FileEvent::FileEvent(int fd)
  : fd_(fd)
  , mask_(AE_NONE)
  , rmask_(AE_NONE)
{}

void 
FileEvent::RegisterReadHandler(Callback cb)
{
  readHandler_ = cb;
  mask_ = mask_ | AE_READABLE;
}

void 
FileEvent::RegisterWriteHandler(Callback cb)
{
  writeHandler_ = cb;
  mask_ = mask_ | AE_WRITABLE;
}
