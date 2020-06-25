#ifndef __JEDIS_HH__
#define __JEDIS_HH__

// #include <string_view>
#include "JString.hh"
#include "JError.hh"

#include <cassert>

#include <string_view>
#include <unordered_map>
#include <mutex>
#include <functional>

#include <boost/any.hpp>
#include <boost/noncopyable.hpp>


namespace  Jedis{


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

  boost::any value()const{
    return value_;
  }

  static JObject createString(const JString& value);
private:

private:
  JDataType type_{JTypeInvalid};
  boost::any value_;
};

inline void swap(JObject &lhs, JObject &rhs)
{
  lhs.swap(rhs);
}

class JDataBase
: boost::noncopyable
{
public:
  static JDataBase* getInstance()
  {
    std::call_once(flag1, std::bind(&JDataBase::init));
    return instance;
  }


  void setValue(std::string_view key, JObject &&value);

  JError getValueByType(std::string_view, JObject *&value, JObject::JDataType type);
  bool isKeyExist(std::string_view key);
  void removeValue(std::string_view key);

private:
  JObject *_getObject(std::string_view key)
  {
    assert(isKeyExist(key));
    return &db_[key];
  }

  static void init() { instance = new JDataBase(); }

  JDataBase() = default;

private:
  std::unordered_map<std::string_view, JObject> db_;
  static std::once_flag flag1;
  static JDataBase *instance;
};


#define G_JDataBase JDataBase::getInstance()

}
#endif

