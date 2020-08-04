//c++ program
//design by >^.^<
//@date    2019-06-23 01:11:25
#include "Buffer.hh"

#include <sys/uio.h>

const char* Buffer::kCrlf = "\r\n";
size_t
Buffer::readv_from(int fd, int* savedErrno)
{
    char extraBuff[65536];
    struct iovec vec[2];
    const size_t writable = writable_size();
    vec[0].iov_base = data() + writeIndex_;
    vec[0].iov_len = writable;
    vec[1].iov_base = extraBuff;
    vec[1].iov_len = sizeof extraBuff;

    // 只有在可写缓冲区大小小于extraBuff时候，才去使用extraBuff
    const int iovcnt = (writable < sizeof(extraBuff)) ? 2 : 1;
    const ssize_t n = readv(fd, vec, iovcnt);
    if(n < 0)
    {
        if(savedErrno)
        *savedErrno = errno;
    }
    else if(n <= writable)
    {
        writeIndex_ += n;
    }
    else{ // n > writable 的时候，此时代表使用了extraBuff
        // 可写缓冲区会被直接读满
        writeIndex_ = buffer_.size();
        append(extraBuff, n - writable);
    }
    return n;
}




