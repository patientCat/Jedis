#ifndef __STRINGUTILS_HH__
#define __STRINGUTILS_HH__

#include <string>

inline
bool StringIsDigit(const std::string& str)
{
  for(auto ch : str)
  {
    if(!ch)
      return false;
  }
  return true;
}

#endif
