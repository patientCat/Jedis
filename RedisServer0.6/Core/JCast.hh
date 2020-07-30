#ifndef __JCAST_HH__
#define __JCAST_HH__

template <typename T>
char *char_cast(T *x)
{
  return reinterpret_cast<char*>(x);
}


template <typename T>
const char *char_cast(const T *x)
{
  return reinterpret_cast<const char*>(x);
}
#endif
