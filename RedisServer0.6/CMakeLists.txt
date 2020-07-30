cmake_minimum_required(VERSION 3.5)
project(my_muduo_net)

set(CMAKE_CXX_FLAGS "-std=c++14 -g -pthread ${CMAKE_CXX_FLAGS}")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


set(CORE_SRCS
  ./Core/JDatabase.cc
  ./Core/Object/JList.cc
  ./Core/Object/JString.cc
  ./Core/JCommand.cc
  ./Core/JReply.cc
  ./Core/PubSub/JPubSubDict.cc
  ./Core/Transaction/Transaction.cc
  )

add_executable(jedis ./jedis.cc  ${CORE_SRCS})
target_link_libraries(jedis muduo_net muduo_base pthread)
