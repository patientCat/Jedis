#ifndef __JSTRING_HH__
#define __JSTRING_HH__

#include "JObject.hh"
#include "StringUtils.hh"

#include <string>
#include <iostream>

class JString
: public JObject
{
public:
  explicit JString(const char* str)
    : JObject()
    , str_(str)
  {
  }
  explicit JString(const std::string& str)
    : JObject()
    , str_(str)
  {
  }
  virtual void* Data() override{
    return &str_;
  }
  virtual void Print() override{
    std::cout << str_ << std::endl;
  }
  ~JString()override = default;
private:
  std::string str_;
};

#endif
