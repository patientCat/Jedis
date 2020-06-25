cmake_minimum_required(VERSION 3.5)
project(my_muduo_net)

set(CMAKE_CXX_FLAGS "-std=c++17 -g -pthread ${CMAKE_CXX_FLAGS}")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(SRCS 
  ./Jedis.cc
  ./JString.cc
  )



add_executable(jedisLocal ./jedisLocal.cc ${SRCS})
