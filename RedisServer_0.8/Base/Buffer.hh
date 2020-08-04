#pragma once

#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <string.h>
#include <assert.h>

#include <string>
#include "Noncopyable.hh"

class Buffer : Noncopyable
{
public:
    static const size_t kPrependSize = 8;
    static const size_t kInitialSize = 1024;
    static const char* kCrlf;

public:
    explicit Buffer(size_t initialSize = kInitialSize)
    : buffer_(kPrependSize + kInitialSize)
    , readIndex_(kPrependSize)
    , writeIndex_(kPrependSize)
    {}

    size_t readable_size() const {   return writeIndex_ - readIndex_;    }
    size_t writable_size() const {   return buffer_.size() - writeIndex_;    }
    size_t prepend_size() const {    return readIndex_;  }

    // 获取可读、可写起始位置处的指针
    const char*peek() const {  return data() + readIndex_; }
    char *peek() {   return data() + readIndex_;   }
    const char* write_index_ptr() const {  return data() + writeIndex_; }
    char * write_index_ptr() {   return data() + writeIndex_;   }

    // 从可读区域里查找\r\n
    const char* find_crlf() const
    {
        const char*crlf = std::search(peek(), write_index_ptr(), kCrlf, kCrlf + 2);
        return crlf == write_index_ptr() ? nullptr : crlf;
    }

    // 从指定开始区域处查找\r\n
    const char* find_crlf(const char* start) const
    {
        const char*crlf = std::search(start, write_index_ptr(), kCrlf, kCrlf + 2);
        return crlf == write_index_ptr() ? nullptr : crlf;
    }

    // 找\n
    const char* find_eof() const
    {
        const void*eof = memchr(peek(), '\n', readable_size());
        return static_cast<const char*>(eof);
    }
    // 找\n
    const char* find_eof(const char* start) const
    {
        const void*eof = memchr(start, '\n', write_index_ptr() - start);
        return static_cast<const char*>(eof);
    }

    // 在将数据从buffer中读取走之后，需同步readIndex_的位置
    void retrieve(size_t len)
    {
        if(len < readable_size())
            readIndex_ += len;
        else
            retrieve_all();
    }

    void retrieve_until(const char* end)
    {
        retrieve(end - peek());
    }

    void retrieve_all()
    {
        readIndex_ = kPrependSize;
        writeIndex_ = kPrependSize;
    }

    std::string retrieve_and_return(size_t len)
    {
        std::string result(peek(), len);
        retrieve(len);
        return result;
    }

    std::string retrieve_all_and_return()
    {
        return retrieve_and_return(readable_size());
    }




    // 添加数据进入缓冲区
    void append(const char* data, size_t len)
    {
        ensure_writable(len);
        std::copy(data, data+len, write_index_ptr());
        writeIndex_ += len;
    }

    void append(const std::string& str)
    {
        append(str.data(), str.size());
    }

    // 注意这个操作一般情况下，仅仅是为了给数据封装一个数据字节数，不会超过8字节的使用
    void prepend(const void* data, size_t len)
    {
        assert(len < prepend_size() );
        readIndex_ -= len;
        const char* d = static_cast<const char*>(data);
        std::copy(d, d+len, peek());
    }

    //void shrinkTo(size_t reserve);

    size_t capacity() const {   return buffer_.capacity();  }

    // 读取数据进缓冲区
    size_t readv_from(int fd, int* savedErrno);
private:
    void ensure_writable(size_t len)
    {
        if(writable_size() < len)
        {
            expand(len);
        }
    }
    char *data()    {   return buffer_.data();  }
    const char* data() const    {   return buffer_.data();  }

    void expand(size_t len)
    {
        if(writable_size() + prepend_size() < len + kPrependSize)
        {
            buffer_.resize(writeIndex_ + len);
        }
        else{
            size_t readable = readable_size();
            std::copy(data() + readIndex_, data() + writeIndex_, data() + kPrependSize);
            readIndex_ = kPrependSize;
            writeIndex_ = readIndex_ + readable;
        }
    }
private:
    std::vector<char> buffer_;
    int readIndex_;
    int writeIndex_;
};



