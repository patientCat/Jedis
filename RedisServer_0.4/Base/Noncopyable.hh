#ifndef __NONCOPYABLE_HH__
#define __NONCOPYABLE_HH__

class Noncoyable
{
protected :
  Noncoyable() = default;
  ~Noncoyable() = default;

  Noncoyable(const Noncoyable &rhs) = delete ;
  void operator=(const Noncoyable &rhs) = delete ;

private:
};
#endif
