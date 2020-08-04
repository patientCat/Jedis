#pragma once

#include <functional>
#include <memory>
#include "Timestamp.hh"

class Buffer;
class TcpConnection;

using TcpConnectionPtr = std::shared_ptr<TcpConnection>;

using MessageCallback = std::function<void(const TcpConnectionPtr& conn, Buffer* buffer, Timestamp receiveTime)>;

using ConnectionCallback = std::function<void(const TcpConnectionPtr&)>;
using CloseCallback = std::function<void(const TcpConnectionPtr&)>;
using WriteCompleteCallback = std::function<void(const TcpConnectionPtr&)>;

using TimerCallback = std::function<void()>;

