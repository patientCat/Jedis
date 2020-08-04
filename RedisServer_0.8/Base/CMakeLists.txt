project(my_muduo_net)

set(BaseSrc
        ./Buffer.cc
        ./Event.cc
        Reactor.cc
        ./Logging.cc
        ./LogStream.cc
        ./TcpConnection.cc
        ./TcpServer.cc
        ./Poller.cc
        )
add_executable(main main.cc ${BaseSrc})