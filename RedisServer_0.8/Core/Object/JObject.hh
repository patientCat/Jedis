#ifndef __JOBJECT_HH__
#define __JOBJECT_HH__

#include "../../Base/Noncopyable.hh"
#include <any>


namespace Jedis{

class JObject
: Noncopyable
{
public:
  enum class JDataType
  {
    JTypeInvalid = 0, 
    JTypeString , 
    JTypeList , 
    JTypeSet , 
    JTypeSortedSet , 
    JTypeHash 
  };
public:
  JObject(JDataType type = JDataType::JTypeInvalid)
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

  void setType(JDataType type)
  {
    type_ = type;
  }

  void swap(JObject & rhs)
  {
    std::swap(value_, rhs.value_);
    this->type_ = rhs.type_;
  }

  template <class T>
  void setValue(T && v)
  {
    value_ = std::forward<T>(v);
  }

  JDataType type() const { return type_; }
  std::any* mutable_value() {
    return &value_;
  }
  const std::any& value() const{
    return value_;
  }

  static JObject createString();
  static JObject createList();
  static JObject createSortedSet();
private:

private:
  JDataType type_{JDataType::JTypeInvalid};
  std::any value_;
};
}
#endif
