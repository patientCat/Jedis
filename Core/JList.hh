#ifndef __JSTRING_HH__
#define __JSTRING_HH__

#include "JObject.hh"

#include <list>

class JList
: public JObject
{
public:
  JList()
    : JObject()
  {
  }
  std::list<JObjectPtr>& Data(){
    return list_;
  }
  ~JList()override = default;
private:
  std::list<JObjectPtr> list_;
};

#endif
