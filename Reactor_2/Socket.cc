
#include <cassert>

#include <errno.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <sys/ioctl.h>
#include <net/if.h>

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
    CloseSocket(fd_);
}

int 
Socket::Bind(int fd, const SocketAddr& addr)
{
  sockaddr_in tmpAddr = addr.GetAddr();
  return  ::bind(fd, (sockaddr*)&tmpAddr, sizeof(tmpAddr));
}

int 
Socket::Listen(int fd)
{
  return ::listen(fd, 5);
}

int 
Socket::Accept(int fd)
{
  return ::accept(fd, NULL, NULL);
}

int Socket::CreateNonBlockTCPSocket()
{
    return ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
}

int Socket::CreateTCPSocket()
{
    return ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void Socket::CloseSocket(int& sock)
{
    if (sock != INVALID_SOCKET)
    {
        ::shutdown(sock, SHUT_RDWR);
        ::close(sock);
        sock = INVALID_SOCKET;
    }
}

void  Socket::SetNonBlock(int sock, bool nonblock)
{
    int flag = ::fcntl(sock, F_GETFL, 0); 
    assert(flag >= 0 && "Non Block failed");

    if (nonblock)
        flag = ::fcntl(sock, F_SETFL, flag | O_NONBLOCK);
    else
        flag = ::fcntl(sock, F_SETFL, flag & ~O_NONBLOCK);
    
}

void Socket::SetNodelay(int sock)
{
    int nodelay = 1;
    ::setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const char*)&nodelay, sizeof(int));
}

void Socket::SetReuseAddr(int sock)
{
    int reuse = 1;
    ::setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse));
}

bool Socket::GetLocalAddr(int  sock, SocketAddr& addr)
{
    sockaddr_in localAddr;
    socklen_t   len = sizeof(localAddr);

    if (0 == ::getsockname(sock, (struct sockaddr*)&localAddr, &len))
    {
        addr.Init(localAddr);
    }
    else
    {
        return  false;
    }

    return  true;
}

bool  Socket::GetPeerAddr(int  sock, SocketAddr& addr)
{
    sockaddr_in  remoteAddr;
    socklen_t    len = sizeof(remoteAddr);
    if (0 == ::getpeername(sock, (struct sockaddr*)&remoteAddr, &len))
    {
        addr.Init(remoteAddr);
    }
    else
    {
        return  false;
    }

    return  true;
}



