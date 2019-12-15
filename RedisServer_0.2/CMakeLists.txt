cmake_minimum_required(VERSION 3.5)
project(my_muduo_net)

add_compile_options("-std=c++11")

set(SRCS 
  ./EventLoop.cc
  ./Event.cc
  ./Poller.cc
  ./Socket.cc
  )


add_executable(testEventLoop ./testEventLoop.cc ${SRCS})
