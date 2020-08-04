project(jedis)

set(CMAKE_CXX_FLAGS "-std=c++17 -g -pthread ${CMAKE_CXX_FLAGS}")
set(BaseSrc
        ./Base/Buffer.cc
        ./Base/Event.cc
        ./Base/Reactor.cc
        ./Base/Logging.cc
        ./Base/LogStream.cc
        ./Base/TcpConnection.cc
        ./Base/TcpServer.cc
        ./Base/Poller.cc
        ./Base/Socket.cc
        ./Base/Timer/TimerQueue.cc
        )

set(CoreSrc
        ./Core/Object/JSortedSet.cc
        ./Core/JDatabase.cc
        ./Core/Object/JList.cc
        ./Core/Object/JString.cc
        ./Core/JCommand.cc
        ./Core/JReply.cc
        ./Core/JedisServer.cc
        ./Core/PubSub/JPubSubDict.cc
        Core/Transaction/JTransaction.cc
        )

add_executable(jedis jedis.cc ${BaseSrc} ${CoreSrc})
