cmake_minimum_required(VERSION 3.16)
project(tmp)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(JObject)
include_directories(PubSub)

add_executable(tmp
        JObject/JList.cc
        JObject/JList.hh
        JObject/JObject.hh
        JObject/JString.cc
        JObject/JString.hh
        PubSub/JPubSubDict.cc
        PubSub/JPubSubDict.hh
        PubSub/Topic.hh
        CMakeLists.txt
        JCast.hh
        JCommand.cc
        JCommand.hh
        Jedis.cc
        Jedis.hh
        JError.hh
        JParams.hh
        JReply.cc
        JReply.hh
        test_any_cast.cc
        test_call_once.cc
        test_string_view.cc Current.hh)
