#ifndef __JOBJECT_HH__
#define __JOBJECT_HH__

#include "JString.hh"
#include <boost/noncopyable.hpp>
#include <boost/any.hpp>

namespace Jedis{

class JObject
: boost::noncopyable
{
public:
  enum JDataType
  {
    JTypeInvalid = 0, 
    JTypeString , 
    JTypeList , 
    JTypeSet , 
    JTypeSortedSet , 
    JTypeHash 
  };
public:
  JObject(JDataType type = JTypeInvalid)
    : type_(type)
  {}
  ~JObject() = default;

  JObject(JObject && rhs)
  {
    swap(rhs);
  }
  JObject &operator=(JObject && rhs)
  {
    swap(rhs);
    return *this;
  }

  JDataType type() const { return type_; }
  void setType(JDataType type)
  {
    type_ = type;
  }

  void swap(JObject & rhs)
  {
    this->value_.swap(rhs.value_);
    this->type_ = rhs.type_;
  }

  template <typename T>
  void setValue(T && v)
  {
    value_ = std::forward<T>(v);
  }

  boost::any& value(){
    return value_;
  }

  static JObject createString(const JString& value);
  static JObject createList();
private:

private:
  JDataType type_{JTypeInvalid};
  boost::any value_;
};
}
#endif
