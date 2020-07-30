//
// Created by Pawn on 2020/7/30.
//

#ifndef TMP_TRANSACTION_H
#define TMP_TRANSACTION_H

#include "boost/noncopyable.hpp"
// 实现事务
// 1. 需要在关联一个Status和TcpConnection。
// 2. 执行命令处需要一个判断。如果开启了事务。则不去执行

struct ConnectionStatus;
class Transaction : public boost::noncopyable{
private:
    Transaction() = default;
public:
    static Transaction & Instance()
    {
        static Transaction instance;
        return instance;
    }
    void multi(ConnectionStatus * s);
    void watch()
    {

    }
    void exec()
    {
        
    }
};


#endif //TMP_TRANSACTION_H

