//
// Created by Pawn on 2020/7/30.
//

#ifndef TMP_TRANSACTION_H
#define TMP_TRANSACTION_H

#include "boost/noncopyable.hpp"
#include <list>
#include <vector>
#include <string>
#include <memory>
// 实现事务
// 1. 需要在关联一个Status和TcpConnection。
// 2. 执行命令处需要一个判断。如果开启了事务。则不去执行

namespace muduo{
  namespace net{
    class TcpConnection;
  }
}

namespace Jedis{
  class ReplyType;

  namespace detail{
    void setTransactionDirtyCas(const std::shared_ptr<muduo::net::TcpConnection> &conn);
  }


class JTransaction : public boost::noncopyable{
private:
public:
    JTransaction() = default;
    JTransaction(JTransaction &&rhs)
    {
      is_mult_flag_ = rhs.is_mult_flag_;
      transaction_queue_ = std::move(rhs.transaction_queue_);
    }
    void operator =(JTransaction && rhs)
    {
      is_mult_flag_ = rhs.is_mult_flag_;
      transaction_queue_ = std::move(rhs.transaction_queue_);
    }

    using StringVec = std::vector<std::string>;
    using JTransactionQueue = std::list<StringVec>;
    
    void executeCommandIsMulti(const StringVec& stringVec, Jedis::ReplyType &reply);

    void set_mult() { is_mult_flag_ = true; }
    bool is_mult()const{ return is_mult_flag_; }
    void set_dirty() { is_dirty_cas_ = true; }
    bool is_dirty()const{ return is_dirty_cas_; }

    void multi()
    {
      reset_status();
      set_mult();
    }
    void watch(const StringVec &keys);
    void exec(ReplyType &reply)
    {
      reset_status();        
      for(auto &packet : transaction_queue_)
      {
        handle_packet(packet, reply);
      }
    }
    void unwatch(const StringVec &keys)
    {
      // 
    }
    void discard()
    {
      reset_status();
    }
    void push_packet(const std::vector<std::string> & packet)
    {
      transaction_queue_.emplace_back(packet);
    }
    void push_packet(std::vector<std::string> && packet)
    {
      transaction_queue_.emplace_back(std::move(packet));
    }
private:
    void handle_packet(const std::vector<std::string> &packet, ReplyType &reply);
    void reset_status()
    {
      is_mult_flag_ = false;
      transaction_queue_.clear();
    }

   bool is_mult_flag_{false}; 
   bool is_dirty_cas_{false};
   JTransactionQueue transaction_queue_;

};

}

#endif //TMP_TRANSACTION_H

