#pragma  once


#include <vector>
#include <string>
#include <list>

#include "../Base/Noncopyable.hh"
#include "./Transaction/JTransaction.hh"

namespace Jedis{
class JConnectionContext : Noncopyable
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
