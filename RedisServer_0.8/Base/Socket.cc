
#include <cassert>

#include <errno.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include <unistd.h>
#if defined(__APPLE__)
#include <unistd.h>
#endif

#include "Socket.hh"
// 实际上就是将socket fd交给Socket管理了
Socket::Socket(int fd) 
  : fd_(fd)
{
}

Socket::~Socket()
{
    close_socket(fd_);
}

int 
Socket::bind(int fd, const SocketAddr& addr)
{
  sockaddr_in tmpAddr = addr.get_sockaddr_in();
  return  ::bind(fd, (sockaddr*)&tmpAddr, sizeof(tmpAddr));
}

int 
Socket::listen(int fd)
{
  return ::listen(fd, 5);
}

int 
Socket::accept(int fd)
{
  return ::accept(fd, NULL, NULL);
}

int Socket::create_nonblock_socket()
{
    return ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
}

int Socket::create_socket()
{
    return ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void Socket::close_socket(int& sock)
{
    if (sock != INVALID_SOCKET)
    {
        ::shutdown(sock, SHUT_RDWR);
        ::close(sock);
        sock = INVALID_SOCKET;
    }
}

void  Socket::set_nonblock(int sock, bool nonblock)
{
    int flag = ::fcntl(sock, F_GETFL, 0); 
    assert(flag >= 0 && "Non Block failed");

    if (nonblock)
        flag = ::fcntl(sock, F_SETFL, flag | O_NONBLOCK);
    else
        flag = ::fcntl(sock, F_SETFL, flag & ~O_NONBLOCK);
    
}

void Socket::set_nodelay(int sock)
{
    int nodelay = 1;
    ::setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const char*)&nodelay, sizeof(int));
}

void Socket::set_reuse_addr(int sock)
{
    int reuse = 1;
    ::setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse));
}

bool Socket::get_local_addr(int  sock, SocketAddr& addr)
{
    sockaddr_in localAddr;
    socklen_t   len = sizeof(localAddr);

    if (0 == ::getsockname(sock, (struct sockaddr*)&localAddr, &len))
    {
        addr.init(localAddr);
    }
    else
    {
        return  false;
    }

    return  true;
}

bool  Socket::get_peer_addr(int  sock, SocketAddr& addr)
{
    sockaddr_in  remoteAddr;
    socklen_t    len = sizeof(remoteAddr);
    if (0 == ::getpeername(sock, (struct sockaddr*)&remoteAddr, &len))
    {
        addr.init(remoteAddr);
    }
    else
    {
        return  false;
    }

    return  true;
}


int 
Socket::read(int fd, void *buffer, int count)
{
  return ::read(fd, buffer, count);
}
int 
Socket::write(int fd, const void *buffer, int count)
{
  return ::write(fd, buffer, count);
}

