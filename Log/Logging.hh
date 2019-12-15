// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#pragma  once
#include "LogStream.hh"
#include "Timestamp.hh"

namespace singsing
{

class Logger
{
 public:
  enum LogLevel
  {
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL,
    NUM_LOG_LEVELS,
  };

  // compile time calculation of basename of source file
  // 用来获取basename的
  class SourceFile
  {
   public:
    template<int N>
    SourceFile(const char (&arr)[N])
      : data_(arr),
        size_(N-1)
    {
      const char* slash = strrchr(data_, '/'); // builtin function
      if (slash)
      {
        data_ = slash + 1;
        size_ -= static_cast<int>(data_ - arr);
      }
    }

    explicit SourceFile(const char* filename)
      : data_(filename)
    {
      // 实际上就是从basename的字符串里面从后向前找/
      const char* slash = strrchr(filename, '/');
      if (slash)
      {
        data_ = slash + 1;
      }
      size_ = static_cast<int>(strlen(data_));
    }

    const char* data_;
    int size_;
  };

  Logger(SourceFile file, int line);
  Logger(SourceFile file, int line, LogLevel level);
  Logger(SourceFile file, int line, LogLevel level, const char* func);
  Logger(SourceFile file, int line, bool toAbort);
  ~Logger();

  LogStream& stream() { return impl_.stream_; }

  static LogLevel logLevel();
  static void setLogLevel(LogLevel level);

  typedef void (*OutputFunc)(const char* msg, int len);
  typedef void (*FlushFunc)();
  static void setOutput(OutputFunc);
  static void setFlush(FlushFunc);

 private:

class Impl
{
 public:
  typedef Logger::LogLevel LogLevel;
  Impl(LogLevel level, int old_errno, const SourceFile& file, int line);
  void formatTime();
  void finish();

  Timestamp time_;
  LogStream stream_;
  LogLevel level_;
  int line_;
  SourceFile basename_;
};

  Impl impl_;

};

extern Logger::LogLevel g_logLevel;

inline Logger::LogLevel Logger::logLevel()
{
  return g_logLevel;
}

//
// CAUTION: do not write:
//
// if (good)
//   LOG_INFO << "Good news";
// else
//   LOG_WARN << "Bad news";
//
// this expends to
//
// if (good)
//   if (logging_INFO)
//     logInfoStream << "Good news";
//   else
//     logWarnStream << "Bad news";
//
// 失败
// Fix 利用do while来修改上面的方式可能出现的错误，
// notice: 不能用do while，也不能再stream后面加分号
#define LOG_TRACE if (singsing::Logger::logLevel() <= singsing::Logger::TRACE) \
  singsing::Logger(__FILE__, __LINE__, singsing::Logger::TRACE, __func__).stream()

#define LOG_DEBUG if (singsing::Logger::logLevel() <= singsing::Logger::DEBUG) \
  singsing::Logger(__FILE__, __LINE__, singsing::Logger::DEBUG, __func__).stream()

#define LOG_INFO if (singsing::Logger::logLevel() <= singsing::Logger::INFO) \
  singsing::Logger(__FILE__, __LINE__).stream()

#define LOG_WARN singsing::Logger(__FILE__, __LINE__, singsing::Logger::WARN).stream()
#define LOG_ERROR singsing::Logger(__FILE__, __LINE__, singsing::Logger::ERROR).stream()
#define LOG_FATAL singsing::Logger(__FILE__, __LINE__, singsing::Logger::FATAL).stream()
#define LOG_SYSERR singsing::Logger(__FILE__, __LINE__, false).stream()
#define LOG_SYSFATAL singsing::Logger(__FILE__, __LINE__, true).stream()

const char* strerror_tl(int savedErrno);

// Taken from glog/logging.h
//
// Check that the input is non NULL.  This very useful in constructor
// initializer lists.

#define CHECK_NOTNULL(val) \
  ::singsing::CheckNotNull(__FILE__, __LINE__, "'" #val "' Must be non NULL", (val))

// A small helper for CHECK_NOTNULL().
template <typename T>
T* CheckNotNull(Logger::SourceFile file, int line, const char *names, T* ptr)
{
  if (ptr == NULL)
  {
   Logger(file, line, Logger::FATAL).stream() << names;
  }
  return ptr;
}

}  // namespace singsing

