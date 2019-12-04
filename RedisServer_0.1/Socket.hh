#ifndef __SOCKET_HH__
#define __SOCKET_HH__

#include <boost/noncopyable.hpp>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <memory>
#include <atomic>
#include <functional>

#define INVALID_SOCKET (int)(~0)
#define SOCKET_ERROR (-1)
#define INVALID_PORT (-1)


struct SocketAddr
{
    SocketAddr()
    {
        Clear();
    }
    
    SocketAddr(const SocketAddr& other)
    {
        memcpy(&addr_, &other.addr_, sizeof addr_);
    }

    SocketAddr& operator= (const SocketAddr&  other)
    {
        if (this != &other)
            memcpy(&addr_, &other.addr_, sizeof addr_);

        return *this;
    }

    SocketAddr(const sockaddr_in& addr)
    {
        Init(addr);
    }

    // ip port format:  127.0.0.1:6379
    SocketAddr(const std::string& ipport)
    {
        std::string::size_type p = ipport.find_first_of(':');
        std::string ip = ipport.substr(0, p);
        std::string port = ipport.substr(p + 1);

        Init(ip.c_str(), static_cast<uint16_t>(std::stoi(port)));
    }

    SocketAddr(uint32_t  netip, uint16_t netport)
    {
        Init(netip, netport);
    }

    SocketAddr(const char* ip, uint16_t hostport)
    {
        Init(ip, hostport);
    }

    void Init(const sockaddr_in& addr)
    {
        memcpy(&addr_, &addr, sizeof(addr));
    }

    void Init(uint32_t netip, uint16_t netport)
    {
        addr_.sin_family = AF_INET;       
        addr_.sin_addr.s_addr = netip;       
        addr_.sin_port = netport;
    }

    void Init(const char* ip, uint16_t hostport)
    {
        addr_.sin_family = AF_INET;
        addr_.sin_addr.s_addr = ::inet_addr(ip);
        addr_.sin_port = htons(hostport);
    }

    sockaddr_in GetAddr() 
    {
      return addr_;
    }
    const sockaddr_in& GetAddr() const
    {
        return addr_;
    }

    const char* GetIP() const
    {
        return ::inet_ntoa(addr_.sin_addr);
    }
    
    const char* GetIP(char* buf, socklen_t size) const
    {
        return ::inet_ntop(AF_INET, (const char*)&addr_.sin_addr, buf, size);
    }

    unsigned short GetPort() const
    {
        return ntohs(addr_.sin_port);
    }
    
    std::string ToString() const
    {
        char tmp[32];
        const char* res = inet_ntop(AF_INET,
                                    &addr_.sin_addr,
                                    tmp,
                                    (socklen_t)(sizeof tmp));

        return std::string(res) + ":" + std::to_string(ntohs(addr_.sin_port));
    }

    bool  Empty() const { return  0 == addr_.sin_family; }
    void  Clear()       { memset(&addr_, 0, sizeof addr_); }
    
    inline friend bool operator== (const SocketAddr& a, const SocketAddr& b)
    {
        return a.addr_.sin_family      ==  b.addr_.sin_family &&
               a.addr_.sin_addr.s_addr ==  b.addr_.sin_addr.s_addr &&
               a.addr_.sin_port        ==  b.addr_.sin_port ;
    }
    
    inline friend bool operator!= (const SocketAddr& a, const SocketAddr& b)
    {
        return !(a == b);
    }

    sockaddr_in addr_;
};

// custom specialization of std::hash can be injected into std
namespace std
{ 
    template<>
    struct hash<SocketAddr> 
    { 
        typedef SocketAddr argument_type; 
        typedef std::size_t result_type; 
        result_type operator()(const argument_type& s) const noexcept 
        {
            result_type h1 = std::hash<short>{}(s.addr_.sin_family); 
            result_type h2 = std::hash<unsigned short>{}(s.addr_.sin_port); 
            result_type h3 = std::hash<unsigned int>{}(s.addr_.sin_addr.s_addr);
            result_type tmp = h1 ^ (h2 << 1);
            return h3 ^ (tmp << 1);
        }
    }; 
}



class Socket : boost::noncopyable
{
public:
    Socket(int fd);
    ~Socket();
    
    int  FD() const { return fd_; }

    static int Bind(int fd, const SocketAddr& addr);
    static int Listen(int fd);
    static int Accept(int fd);

    static int CreateTCPSocket();
    static void CloseSocket(int &sock);
    static void SetNonBlock(int sock, bool nonBlock = true);
    static void SetNodelay(int sock);
    static void SetReuseAddr(int sock);
    static bool GetLocalAddr(int sock, SocketAddr& );
    static bool GetPeerAddr(int sock,  SocketAddr& );
    static void GetMyAddrInfo(unsigned int* addrs, int num);

private:
    int fd_;
};


#endif

