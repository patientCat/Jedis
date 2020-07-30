#pragma once

#include <string>

#include "muduo/net/TcpConnection.h"
#include <set>

using namespace muduo;
using namespace muduo::net;
class Topic
{
public:
  Topic(const std::string& topic_name)
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

  void publish(const string& content, Timestamp time)
  {
    content_ = content;
    lastPubTime_ = time;
    string message = makeMessage();
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
    string makeMessage()
    {
      string res;
      res += "1)\"message\"\r\n";
      res += "2)\"" + topic_ + "\"\r\n";
      res += "3)\"" + content_ + "\"\r\n";
      return res;
    }
  
  std::string topic_;
  std::string content_;
  Timestamp lastPubTime_;
  std::set<TcpConnectionPtr> audiences_;
};
