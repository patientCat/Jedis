
/*
 * 实现一个固定大小的buffer，被LogStream来使用
 */
#pragma once

#include "Noncopyable.hh"
#include <string.h>

#include <string>

namespace detail{

template<int SIZE>
class FixedBuffer : Noncopyable
{
public:
    FixedBuffer() : cur_(data_) {   setCookie(cookieStart); }
    ~FixedBuffer() {    setCookie(cookieEnd);   }

    void append(const char* buf, size_t len)
    {
        if(avail() > len)
        {
            memcpy(cur_, buf, len);
            cur_ += len;
        }
    }

    const char* data() const { return data_; }
    // 返回缓冲区被占有的长度
    int length() const { return static_cast<int>(cur_ - data_); }
    char * current() { return cur_; }
    int avail() const { return static_cast<int>(end() - cur_); }
    void add(size_t len) { cur_ += len; }

    void reset() { cur_ = data_; }
    void bzero() { memset(data_, 0, sizeof data_); }

    // for used by GDB
    const char* debugString();
    void setCookie(void (*cookie)())    {   cookie_ = cookie;   }
    std::string toString() const {  return std::string(data_, length());    }
private:
    const char* end() const {   return data_ + SIZE;  }
    static void cookieStart();
    static void cookieEnd();

    void (*cookie_)();
    char data_[SIZE];
    char *cur_;
};
} // end namespace detail

using namespace detail;

template <int SIZE>
const char* FixedBuffer<SIZE>::debugString()
{
    *cur_ = '\0';
    return data_;
}

template <int SIZE>
void FixedBuffer<SIZE>::cookieStart()
{
}

template <int SIZE>
void FixedBuffer<SIZE>::cookieEnd()
{
}

