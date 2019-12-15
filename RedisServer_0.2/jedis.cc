//c++ program
//design by >^.^<
//@date    2019-12-03 06:45:14
#include "../Log/easylogging++.h"
#include "Socket.hh"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

INITIALIZE_EASYLOGGINGPP

class Server
{
public:
private:
};
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

void onAccept(int fd)
{
  int cfd = Socket::Accept(fd);
  Socket::SetNonBlock(cfd);
  FileEventPtr eventPtr = make_shared<FileEvent>(cfd);
  eventPtr->RegisterReadHandler(onReading);
  loop.RegisterFileEvent(eventPtr);
}
int main()
{
}
