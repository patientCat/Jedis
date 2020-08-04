#ifndef __TelnetCodec__
#define __TelnetCodec__


/**
 * 这是一个专门用来解析Telnet协议包的中间层
 * 实际上就是将Telnet协议的字节流，以\r\n结束
 * 然后转成一个完整的包。
 */



#include <boost/noncopyable.hpp>
#include <functional>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "muduo/net/TcpConnection.h"
#include "muduo/base/Logging.h"
#include "muduo/base/Timestamp.h"

using namespace muduo::net;
using namespace muduo;


inline std::vector<string> split(const string &s, const string &seperator){
  std::vector<string> result;
  typedef string::size_type string_size;
  string_size i = 0;

  while(i != s.size()){
    //找到字符串中首个不等于分隔符的字母；
    int flag = 0;
    while(i != s.size() && flag == 0){
      flag = 1;
      for(string_size x = 0; x < seperator.size(); ++x)
      {
        if(s[i] == seperator[x]){
          ++i;
          flag = 0;
          break;
        }
      }
    }

    //找到又一个分隔符，将两个分隔符之间的字符串取出；
    flag = 0;
    string_size j = i;
    while(j != s.size() && flag == 0){
      for(string_size x = 0; x < seperator.size(); ++x)
        if(s[j] == seperator[x]){
          flag = 1;
          break;
        }
      if(flag == 0)
        ++j;
    }
    if(i != j){
      result.push_back(s.substr(i, j-i));
      i = j;
    }
  }
  return result;
}

inline std::string  strip_space(const std::string & x)
{
  string res;
  for(int i = 0; i < x.size(); i++)
  {
    if(!isspace(x[i]))
    {
      res.push_back(x[i]);
    }
  }
  return res;
}

class TelnetCodec
: boost::noncopyable
{
  public:
    //  using StringVectorCallback = std::function<void (const TcpConnectionPtr& conn, const std::vector<std::string>& stringVec, Timestamp recvTime)>;
    typedef std::function<void (const TcpConnectionPtr& conn, const std::vector<std::string>& stringVec, muduo::Timestamp recvTime)> StringVectorCallback;
  public:
    TelnetCodec(const StringVectorCallback& cb)
      : callback_(cb)
    {
    }

    TelnetCodec(StringVectorCallback && cb)
      : callback_(cb)
    {
    }

    // 当数据到来时，这个函数应该被回调。但是需要来判断是否收到一个消息。如果消息到来，则回调给上层
    // 如果消息没有到来则，不应该回调
    void onMessage(const TcpConnectionPtr& conn, Buffer *buffer, muduo::Timestamp receiveTime)
    {
      using namespace std;
      LOG_INFO << "TelnetCodec onMessage";
      // 这里设置了个条件，就是最大允许数据包只能是65536个字节。
      const char *start = buffer->peek();
      const char *end = buffer->findCRLF();
      if(!end)
        return;

      int len = end - start;
      if(!len)
        return;
      string packet(start, end);
      buffer->retrieve(len + 2);

      auto stringVec = split(packet, " \r\n");
      for(auto &x : stringVec)
        cout << x << endl;
      callback_(conn, stringVec, receiveTime);
    }

    /**
     *  这里希望是能将stringVec转成  str1 str2 str3 str4\r\n的协议格式就可以了
     */
    void send(const TcpConnectionPtr& conn, const std::string& str)
    {
      auto message = str + "\r\n";
      conn->send(message);
    }

  private:
    StringVectorCallback callback_;
};
#endif 
// __TelnetCodec__
