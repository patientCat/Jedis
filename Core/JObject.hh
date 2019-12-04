#ifndef __JOBJECT_HH__
#define __JOBJECT_HH__

#include <memory>

class JObject;
using JObjectPtr = std::shared_ptr<JObject>;

class JObject 
{
public:
  JObject() = default;
  JObject(const JObject& obj) = delete;
  JObject &operator=(const JObject& obj) = delete;

  virtual void * Data() = 0;
  // for test
  virtual void Print() = 0;

  virtual ~JObject() = 0;

private:
};
#endif

