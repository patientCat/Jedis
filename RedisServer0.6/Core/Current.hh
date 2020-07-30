//
// Created by Pawn on 2020/7/30.
//

#ifndef TMP_CURRENT_HH
#define TMP_CURRENT_HH

#include "muduo/net/TcpConnection.h"
#include <unordered_map>
#include <memory>


struct TransactionStatus
{
};

struct ConnectionStatus
{
  bool is_multi_flag{false}; // 是否开启了事务
  // 命令队列存放命令
};


// 持有weak指针是为了让客户端可以安全断开
class Current
{
public:
    typedef std::weak_ptr<muduo::net::TcpConnection> WeakTcpConnectionPtr;
    typedef muduo::net::TcpConnection* RawTcpConnectionPtr;
    typedef std::unordered_map<RawTcpConnectionPtr,ConnectionStatus*> ConnectionStatusMap;

    // 如果连接存在，返回sp指针和其状态，否则返回nullptr
    static muduo::net::TcpConnectionPtr CurrentTcpConnection(const muduo::net::TcpConnectionPtr& conn = NULL)
    {
        static WeakTcpConnectionPtr curr_conn;
        if(conn)
        {
            curr_conn = conn;
        }

        muduo::net::TcpConnectionPtr res_conn = curr_conn.lock();
        if(res_conn)
        {
          return res_conn;
        }
       return nullptr;
    }

    static void RemoveTcpConnectionStatus(const muduo::net::TcpConnectionPtr&conn)
    {
      auto &status_map = GetConnectionStatusMap();
      if(status_map.count(conn.get()))
        status_map.erase(conn.get()); 
    }
    static void SetTcpConnectionStatus(const muduo::net::TcpConnectionPtr&conn)
    {
      auto &status_map = GetConnectionStatusMap();
      if(!status_map.count(conn.get()))
        status_map.insert({conn.get(), new ConnectionStatus}); 
    }

    static ConnectionStatus* CurrentTcpConnectionStatus()
    {
      auto conn = CurrentTcpConnection();
      if(!conn)
      {
        // 如果连接已经不存在了，就将其在map中删除
        auto iter = GetConnectionStatusMap().find(conn.get());
        if(iter != GetConnectionStatusMap().end())
          GetConnectionStatusMap().erase(iter);
      }else{
        return GetStatusOf(conn);
      }

      return nullptr;
    }

  private:

    static ConnectionStatusMap& GetConnectionStatusMap()
    {
      static  ConnectionStatusMap conn_status_map;
      return conn_status_map;
    }

    // 向连接状态表中插入状态
    static void SetStatusOf(const muduo::net::TcpConnectionPtr conn, ConnectionStatus *status)
    {
      GetConnectionStatusMap().insert({conn.get(), status}); 
    }

    // 状态一定存在
    static ConnectionStatus* GetStatusOf(const muduo::net::TcpConnectionPtr conn)
    {
      auto &conn_status_map = GetConnectionStatusMap();
      RawTcpConnectionPtr pconn = conn.get();
      if(conn_status_map.count(pconn) == 0)
      {
        assert(false); //不可能发生
      }else{
        return conn_status_map[pconn];
      }
      return nullptr; // 不可能发生
    }
private: 
};

#endif //TMP_CURRENT_HH
