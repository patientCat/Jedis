//c++ program
//design by >^.^<
//@date    2020-07-28 07:49:11
#include <iostream>
#include "./Core/JedisServer.hh"
#include "muduo/net/InetAddress.h"

void init_log()
{
  Logger::setLogLevel(Logger::TRACE);
}
int main()
{
  init_log();

  SocketAddr addr("127.0.0.1", 8888);
  JedisServer server(addr);
  server.start();
}
