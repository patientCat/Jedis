//
// Created by Pawn on 2020/7/30.
//

#ifndef TMP_CURRENT_HH
#define TMP_CURRENT_HH

#include "../Base/TcpConnection.hh"
#include <unordered_map>
#include <memory>


// 持有weak指针是为了让客户端可以安全断开
class JCurrent {
public:
    typedef std::weak_ptr<TcpConnection> WeakTcpConnectionPtr;

    // 如果连接存在，返回sp指针和其状态，否则返回nullptr
    static TcpConnectionPtr CurrentTcpConnection(const TcpConnectionPtr& conn = NULL)
    {
        static WeakTcpConnectionPtr curr_conn;
        if(conn)
        {
            curr_conn = conn;
        }

        TcpConnectionPtr res_conn = curr_conn.lock();
        if(res_conn)
        {
          return res_conn;
        }
       return nullptr;
    }

private: 
};

#endif //TMP_CURRENT_HH
