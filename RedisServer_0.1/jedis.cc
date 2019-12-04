//c++ program
//design by >^.^<
//@date    2019-12-03 06:45:14
#include "Socket.hh"

#include <stdio.h>


#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

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
void onReading(int cfd)
{
  char buff[1024] = {0};
  // 读取一个字节的*
  int n = read(cfd, buff, 1024);
  parser(buff, n); 
}

int main()
{
  Socket listenSocket(Socket::CreateTCPSocket());
  SocketAddr addr("127.0.0.1:8888"); 
  // listen
  Socket::Bind(listenSocket.FD(), addr);
  Socket::Listen(listenSocket.FD());

  int cfd = Socket::Accept(listenSocket.FD());
  onReading(cfd);
}
