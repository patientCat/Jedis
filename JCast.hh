#ifndef __JCAST_HH__
#define __JCAST_HH__


template <class T>
char *char_cast(T *t)
{
  return reinterpret_cast<char*>(t);
}

template <class T>
const char *char_cast(const T *t)
{
  return reinterpret_cast<const char*>(t);
}
#endif
