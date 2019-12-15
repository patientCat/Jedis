//c++ program
//design by >^.^<
//@date    2019-12-03 06:45:14
#include "TcpServer.hh"

#include <stdio.h>
#include <string.h>

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <functional>

using namespace std;

class EchoServer
{
public:
  explicit EchoServer(const SocketAddr& addr)
    : server_(addr)
    , addr_(addr)
  {
    server_.SetConnectionCallback(std::bind(&EchoServer::OnConnection, this, std::placeholders::_1));
    server_.SetMessageCallback(std::bind(&EchoServer::OnMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
  }

  void Start()
  {
    server_.Start();
  }
  void OnConnection(TcpConnectionPtr connPtr)
  {
    cout << ">>>>>> new connection" << endl;
  }

  void OnMessage(TcpConnectionPtr connPtr, Buffer *buff, Timestamp ts)
  {
    string recv = buff->returnAllStringAndUpdate();
    connPtr->Send(recv.data(), recv.size());
  }

private:
  TcpServer server_;
  SocketAddr addr_;
};

/*
void parser(char *buff, int maxLen)
{
  const char *crlf = "\r\n";
  char *start = buff;
  char * end = strstr(buff, crlf); 
  string res(start, end);
  stringstream ss(res); 
  while(!ss.eof())
  {
    string word;
    ss >> word;
    cout << word << endl;
  }
}
*/

int main()
{
  Logger::setLogLevel(Logger::LogLevel::DEBUG);
  SocketAddr addr("127.0.0.1:8888");
  EchoServer server(addr);
  server.Start();
}
