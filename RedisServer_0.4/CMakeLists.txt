cmake_minimum_required(VERSION 3.5)
project(my_muduo_net)

add_compile_options("-std=c++11")
add_compile_options("-g")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(SRCS 
  ./Buffer.cc
  ./EventLoop.cc
  ./Event.cc
  ./Logging.cc
  ./LogStream.cc
  ./Poller.cc
  ./Socket.cc
  ./TcpConnection.cc
  )


#add_executable(testConn ./testTcpConnection.cc ${SRCS})
add_executable(echoServer ./echoServer.cc ${SRCS})
