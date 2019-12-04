cmake_minimum_required(VERSION 3.5)
project(my_muduo_net)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)
add_compile_options("-std=c++11")

set(SRCS 
  ./jedis.cc
  ./Socket.cc
  ../Log/easylogging++.cc
  )


add_executable(jedis ${SRCS})
