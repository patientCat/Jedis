#ifndef __NONCOPYABLE_HH__
#define __NONCOPYABLE_HH__

class Noncopyable
{
protected :
  Noncopyable() = default;
  ~Noncopyable() = default;

  Noncopyable(const Noncopyable &rhs) = delete ;
  void operator=(const Noncopyable &rhs) = delete ;

private:
};
#endif
