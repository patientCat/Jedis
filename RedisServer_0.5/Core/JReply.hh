#ifndef __JREPLY_HH__
#define __JREPLY_HH__

#include <string>
#include <sstream>
#include <utility>
#include "JError.hh"
#include "JObject.hh"
#include "JString.hh"

namespace Jedis{


using ReplyType = std::stringstream;

class ReplyError
{
public:
  static void setReply(const void*start, int len, ReplyType &reply)
  {
    reply.write((char*)(start), len);
  }
  static void setReply(JError err, ReplyType &reply)
  {
    std::string str;
    switch(err)
    {
      case JError_InvalidType:
        str = kErrInvalidType;
        break;
      case JError_MismatchType:
        str = kErrMismatchTypeStr;
        break;
      case JError_KeyNotExist: 
        str = kErrKeyNotExistStr;
        break;
      case JError_ParamNum:
        str = kErrParams;
        break;
      case JError_CmdNotExist:
        str = kErrCmdNotExist;
        break;
      case JError_InvalidParamFormat:
        str = kErrInvalidParamFormat;
        break;
      case JError_OK:
        str = kErrOk;
        break;
      default:
        throw std::logic_error("没有这种错误类型");
    }
    char format[1024] = {0};
    int n = sprintf(format, "----->[%s]: ", str.c_str());
    reply.write(format, n);
  }

private:
  static const std::string kErrMismatchTypeStr;
  static const std::string kErrKeyNotExistStr;
  static const std::string kErrInvalidType;
  static const std::string kErrParams;
  static const std::string kErrCmdNotExist;
  static const std::string kErrInvalidParamFormat;
  static const std::string kErrOk;

  static const std::string kJianTou;
};

  // TODO: make it movable
std::pair<JError, JObject*> checkKey(const JString& para, ReplyType& reply, JObject::JDataType objType);
}
#endif
