#pragma once



// 用作订阅和退订的字典

#include <unordered_map>

#include "Topic.hh"

/*
 * 走一遍处理逻辑流程
 * 订阅完成之后。当有人针对某个topic发布消息时，提交publish "this_topic" "a hello message"
 * 
 */

class JPubSubDict
{
  public:

    static JPubSubDict & Instance() {
        static JPubSubDict pubsub;
        return pubsub;
    }
    void publish(const Jedis::JString& topic_name, const Jedis::JString& content, Timestamp time_stamp)
    {
      // 当前不管正则处理
      if(hashmap_.count(topic_name))
      {
        auto &topic = hashmap_[topic_name];
        topic->publish(content, time_stamp);
      }
      // 如果topic不存在, 返回错误
    }
    // 订阅
    void subscribe(Jedis::JString topic_name, const TcpConnectionPtr & conn)
    {
      if(!hashmap_.count(topic_name))
      {
        // 新建一个topic
        hashmap_.insert({topic_name, std::make_unique<Topic>(topic_name)});
      }else{
        auto &topic = hashmap_[topic_name];
        if(topic->has_conn(conn))
        {
          // LOG_TRACE 该topic已经被conn订阅
          return;
        }
      }
      auto &curr_topic = hashmap_[topic_name];
      curr_topic->add(conn);
    }

    // 退订
    void unSubscribe(Jedis::JString topic_name, const TcpConnectionPtr & conn)
    {
      auto &topic = hashmap_[topic_name];
      if(!topic->has_conn(conn))
      {
        return ; // 该topic下没有这个连接，不用删除
      }
      topic->remove(conn);
    }

    // 退订该连接的所有topic, 这样的话，就需要让连接知道自己订阅了哪些topic
    void unSubscribe(const TcpConnectionPtr &conn);

  private:
    std::unordered_map<Jedis::JString, std::unique_ptr<Topic>> hashmap_;
};
