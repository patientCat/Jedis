#pragma once

#include <iostream>
#include <stdexcept>

#include "JReply.hh"

namespace Jedis{

  class JError : public std::exception
  {
    public:
      virtual void error_handler(JReply & reply)
      {

      }
  };

  class JError_InvalidType
    : public JError
  {
    public:
      void error_handler(JReply &reply) override {}
  };
  class JError_KeyNotExist
    : public JError
  {
    public:
      void error_handler(JReply &reply) override {
        reply.setReply(JReply::JReplyType::Key_Not_Exist);
      }
  };
  class JError_MismatchType
    : public JError
  {

    public:
      void error_handler(JReply &reply) override {
        reply.setReply(JReply::JReplyType::Mismatch_Type);
      }
  };
  class JError_ParamNum
    : public JError
  {

    public:
      void error_handler(JReply &reply) override {
        reply.setReply(JReply::JReplyType::Params_Num_Error);
      }
  };

  class JError_CmdNotExist
    : public JError
  {

    public:
      void error_handler(JReply &reply) override {
        reply.setReply(JReply::JReplyType::Command_Not_Exist);
      }
  };
}// end namespace Jedis
