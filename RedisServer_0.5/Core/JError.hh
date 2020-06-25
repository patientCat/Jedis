#ifndef __JERROR_HH__
#define __JERROR_HH__

#include <iostream>

namespace Jedis{

enum JError
{
  JError_OK = 0,
  JError_InvalidType,
  JError_KeyNotExist,
  JError_MismatchType,
  JError_ParamNum,
  JError_CmdNotExist,
  JError_InvalidParamFormat,
}; 

}
#endif
