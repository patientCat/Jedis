cmake_minimum_required(VERSION 3.5)
project(my_muduo_net)

set(CMAKE_CXX_FLAGS "-std=c++17 -g -pthread ${CMAKE_CXX_FLAGS}")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(BASE_SRCS 
  ./Base/Buffer.cc
  ./Base/Reactor.cc
  ./Base/Event.cc
  ./Base/Logging.cc
  ./Base/LogStream.cc
  ./Base/Poller.cc
  ./Base/Socket.cc
  ./Base/TcpConnection.cc
  ./Base/TcpServer.cc
  ./Base/Timer/TimerQueue.cc
  )


#add_executable(testConn ./testTcpConnection.cc ${SRCS})
add_executable(echoStringServer ./echoStringServer.cc ${BASE_SRCS})
