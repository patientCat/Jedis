#pragma  once


#include <vector>
#include <string>
#include <list>

#include "./Transaction/Transaction.hh"
#include <boost/noncopyable.hpp>

namespace Jedis{
class JConnectionContext : boost::noncopyable
{
  public:
    JConnectionContext() = default;
    JConnectionContext(JConnectionContext && rhs)
    {
      transaction_ = std::move(rhs.transaction_);
    }
    JTransaction &get_transaction()
    {
      return transaction_;
    } 

  private:
    JTransaction transaction_;
};
}
