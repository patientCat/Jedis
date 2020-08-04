#pragma once

#include <sstream>
#include <utility>
#include <type_traits>
#include "./Object/JString.hh"

namespace Jedis{


  class JReply {
    public:
      enum class JReplyType{
        OK,
        Key_Already_Exist,
        Key_Not_Exist,
        Para_Format_Error,
        Command_Not_Exist,
        Params_Num_Error,
        Mismatch_Type,
        Duplicate_Multi,
      };
    public:
      void put(char x)
      {
        reply.put(x);
      }
      void append(void *data, int len)
      {
        reply.write((char*)data, len);
      }
      Jedis::JString getString()
      {
        return reply.str();
      }
      std::stringstream & getStream()
      {
        return reply;
      }
      void reset()
      {
        reply.str("");
      }

      template <class T>
        std::enable_if<std::is_arithmetic<T>::value, void> setReply(T arithmetic_value)
        {
          setReply(std::to_string(arithmetic_value));
        }
      void setReply(const JString& str)
      {
        setReply(str.data(), str.size()) ;
      }
      void setReply(const void*start, int len)
      {
        reply.write((char*)(start), len);
      }
      void setReply(JReplyType type = JReplyType::OK)
      {
        Jedis::JString str;
        switch(type)
        {
          case JReplyType::OK:
            str = kErrOk;
            break;
          case JReplyType::Key_Already_Exist:
            str = kErrKeyAleadyExistStr;
            break;
          case JReplyType::Key_Not_Exist :
            str = kErrKeyNotExistStr;
            break;
          case JReplyType::Para_Format_Error:
            str = kErrInvalidParamFormat;
            break;
          case JReplyType::Command_Not_Exist:
            str = kErrCmdNotExist;
            break;
          case JReplyType::Params_Num_Error:
            str = kErrParamsNum;
            break;
          case JReplyType::Mismatch_Type:
            str = kErrMismatchTypeStr;
            break;
          case JReplyType::Duplicate_Multi:
            str = kErrDuplicateMultStr;
            break;
          default:
            throw std::logic_error("没有这种错误类型");
        }
        char format[1024] = {0};
        int n = sprintf(format, "----->[%s]: ", str.c_str());
        reply.write(format, n);
      }

    private:
      std::stringstream reply;

    private:
      static const Jedis::JString kErrMismatchTypeStr;
      static const Jedis::JString kErrKeyNotExistStr;
      static const Jedis::JString kErrKeyAleadyExistStr;
      static const Jedis::JString kErrInvalidType;
      static const Jedis::JString kErrParamsNum;
      static const Jedis::JString kErrCmdNotExist;
      static const Jedis::JString kErrInvalidParamFormat;
      static const Jedis::JString kErrOk;
      static const Jedis::JString kJianTou;
      static const Jedis::JString kErrDuplicateMultStr;
  };

  // TODO: make it movable
} // end namespace jedis
