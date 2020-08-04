//
// Created by Pawn on 2020/8/1.
//

#include "TcpServer.hh"

#include <functional>
#include <iostream>
using namespace std;

TcpServer * TcpServer::instance_ = nullptr;
void
TcpServer::remove_connection(const TcpConnectionPtr &ptr) {
    LOG_DEBUG << "remove Connection";
    reactor_->run_in_loop(
        std::bind(&TcpServer::remove_connection_in_loop, this, ptr));
}

void
TcpServer::remove_connection_in_loop(const TcpConnectionPtr &ptr) {
    int fd = ptr->fd();
    // auto copy = ptr;
    tcpConnectionPtrList_.erase(fd);

    // std::bind 可以持有sp指针，且会增加引用计数。
    reactor_->run_in_loop(
        std::bind(&TcpConnection::connection_destroyed, ptr));
}

void
TcpServer::on_new_connection(int cfd) {
    SocketAddr peerAddr;
    Socket::get_peer_addr(cfd, peerAddr);
    LOG_INFO << "new connection " << peerAddr.to_string() << " is established";
    TcpConnectionPtr ptr(new TcpConnection(reactor_, cfd, peerAddr), [](TcpConnection*){
        LOG_TRACE << "TcpConnection安全析构";
        });
    tcpConnectionPtrList_[cfd] = ptr;
    ptr->set_status(ConnectionStatus::kConnected);

    if(connectionCallback_)
        connectionCallback_(ptr);
// 这里需要注册TcpConnection的回调函数

    ptr->set_connection_callback(connectionCallback_);
    ptr->set_message_callback(messageCallback_);
    ptr->set_write_complete_callback(writeCallback_);
    ptr->set_close_callback(std::bind(&TcpServer::remove_connection, this, std::placeholders::_1));
}

