#ifndef __NONCOPYABLE_HH__
#define __NONCOPYABLE_HH__

class Noncopyable
{
protected: 
  Noncopyable() = default;
  ~Noncopyable() = default;
public:
  Noncopyable(const Noncopyable&) = delete;
  Noncopyable(Noncopyable &&) = delete;
  Noncopyable &operator=(const Noncopyable&) = delete;
  Noncopyable &operator=(Noncopyable&&) = delete;
};
#endif
