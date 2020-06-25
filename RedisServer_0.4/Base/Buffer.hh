#pragma once

#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <string.h>
#include <assert.h>

class Buffer
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

    size_t readableSize() const {   return writeIndex_ - readIndex_;    }
    size_t writableSize() const {   return buffer_.size() - writeIndex_;    }
    size_t prependSize() const {    return readIndex_;  }

    // 获取可读、可写起始位置处的指针
    const char* readIndexPtr() const {  return data() + readIndex_; }
    char * readIndexPtr() {   return data() + readIndex_;   }
    const char* writeIndexPtr() const {  return data() + writeIndex_; }
    char * writeIndexPtr() {   return data() + writeIndex_;   }

    // 从可读区域里查找\r\n
    const char* findCRLF() const
    {
        const char*crlf = std::search(readIndexPtr(), writeIndexPtr(), kCrlf, kCrlf + 2);
        return crlf == writeIndexPtr() ? nullptr : crlf;
    }

    // 从指定开始区域处查找\r\n
    const char* findCRLF(const char* start) const
    {
        const char*crlf = std::search(start, writeIndexPtr(), kCrlf, kCrlf + 2);
        return crlf == writeIndexPtr() ? nullptr : crlf;
    }

    // 找\n
    const char* findEOF() const
    {
        const void*eof = memchr(readIndexPtr(), '\n', readableSize());
        return static_cast<const char*>(eof);
    }
    // 找\n
    const char* findEOF(const char* start) const
    {
        const void*eof = memchr(start, '\n', writeIndexPtr() - start);
        return static_cast<const char*>(eof);
    }

    // 在将数据从buffer中读取走之后，需同步readIndex_的位置
    void updateReadIndex(size_t len)
    {
        if(len < readableSize())
            readIndex_ += len;
        else
            updateReadIndexAll();
    }

    void updateReadIndexUntil(const char* end)
    {
        updateReadIndex(end - readIndexPtr());
    }

    void updateReadIndexAll()
    {
        readIndex_ = kPrependSize;
        writeIndex_ = kPrependSize;
    }

    std::string returnStringAndUpdate(size_t len)
    {
        std::string result(readIndexPtr(), len);
        updateReadIndex(len);
        return result;
    }

    std::string returnAllStringAndUpdate()
    {
        return returnStringAndUpdate(readableSize());
    }

    void ensureWritable(size_t len)
    {
        if(writableSize() < len)
        {
            expand(len);
        }
    }

    // 添加数据进入缓冲区
    void append(const char* data, size_t len)
    {
        ensureWritable(len);
        std::copy(data, data+len, writeIndexPtr());
        writeIndex_ += len;
    }

    void append(const std::string& str)
    {
        append(str.data(), str.size());
    }

    // 注意这个操作一般情况下，仅仅是为了给数据封装一个数据字节数，不会超过8字节的使用
    void prepend(const void* data, size_t len)
    {
        assert(len < prependSize() );
        readIndex_ -= len;
        const char* d = static_cast<const char*>(data);
        std::copy(d, d+len, readIndexPtr());
    }

    //void shrinkTo(size_t reserve);

    size_t capacity() const {   return buffer_.capacity();  }

    // 读取数据进缓冲区
    size_t readFd(int fd, int* savedErrno);
private:
    char *data()    {   return buffer_.data();  }
    const char* data() const    {   return buffer_.data();  }

    void expand(size_t len)
    {
        if(writableSize() + prependSize() < len + kPrependSize)
        {
            buffer_.resize(writeIndex_ + len);
        }
        else{
            size_t readable = readableSize();
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



