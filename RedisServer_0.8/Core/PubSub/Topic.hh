#pragma once

#include "../Object/JString.hh"

#include "../../Base/TcpConnection.hh"
#include <set>

class Topic
{
public:
  Topic(const Jedis::JString& topic_name)
    : topic_(topic_name)
  {
  }

  // 这里用sp指针么？
  void add(const TcpConnectionPtr &conn)
  {
    audiences_.insert(conn);
    if(lastPubTime_.valid())
    {
      conn->send(makeMessage());
    }
  }

  void remove(const TcpConnectionPtr& conn)
  {
    audiences_.erase(conn);
  }

  void publish(const Jedis::JString& content, Timestamp time)
  {
    content_ = content;
    lastPubTime_ = time;
    Jedis::JString message = makeMessage();
    for(auto conn : audiences_)
    {
      conn->send(message);
    }
  }

  bool has_conn(const TcpConnectionPtr &conn)
  {
    for(auto conn_in_set : audiences_)
    {
      if(conn_in_set == conn)
        return true;
    }
    return false;
  }
private:
  Jedis::JString makeMessage()
    {
      Jedis::JString res;
      res += "1)\"message\"\r\n";
      res += "2)\"" + topic_ + "\"\r\n";
      res += "3)\"" + content_ + "\"\r\n";
      return res;
    }
  
  Jedis::JString topic_;
  Jedis::JString content_;
  Timestamp lastPubTime_;
  std::set<TcpConnectionPtr> audiences_;
};
