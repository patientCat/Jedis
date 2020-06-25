#ifndef __TelnetCodec__
#define __TelnetCodec__


/**
 * 这是一个专门用来解析Telnet协议包的中间层
 * 实际上就是将Telnet协议的字节流，以\r\n结束
 * 然后转成一个完整的包。
 */


#include "./Base/Callback.hh"
#include "./Base/Timestamp.hh"
#include "./Base/Buffer.hh"
#include "./Base/TcpConnection.hh"
#include "./Base/Logging.hh"

#include <boost/noncopyable.hpp>
#include <functional>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

class TelnetCodec
: boost::noncopyable
{
public:
  using StringVectorCallback = std::function<void (const TcpConnectionPtr& conn, const std::vector<std::string>& stringVec, Timestamp recvTime)>;
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
  void onMessage(const TcpConnectionPtr& conn, Buffer *buffer, Timestamp receiveTime)
  {
    using namespace std;
    LOG_INFO << "TelnetCodec onMessage";
    // 这里设置了个条件，就是最大允许数据包只能是65536个字节。
    char *start = buffer->readIndexPtr();
    const char *end = buffer->findCRLF();
    if(!end)
      return;

    int len = end - start;
    if(!len)
      return;
    // 这里用StringStream来读取输入
    std::istringstream ss(std::string(start, len));
    std::vector<std::string> stringVec;
    while(!ss.eof())
    {
      std::string word;
      ss >> word;
      cout << word << endl;
      stringVec.emplace_back(word);  
    }

    buffer->updateReadIndex(len + 2);
    callback_(conn, stringVec, receiveTime);
  }

  /**
   *  这里希望是能将stringVec转成  str1 str2 str3 str4\r\n的协议格式就可以了
   */
  void send(const TcpConnectionPtr& conn, const std::vector<std::string>& stringVec)
  {
    std::stringstream ss; 
    for(int i = 0; i < stringVec.size(); i++)
    {
      ss << stringVec[i] ;
      if(i != stringVec.size() - 1)
      {
        ss << ' ';
      }
    }
    ss << "\r\n";
    conn->Send(ss.str().data(), ss.str().size());
  }

private:
  StringVectorCallback callback_;
};
#endif 
// __TelnetCodec__
