//c++ program
//design by >^.^<
//@date    2019-12-15 05:02:25
#include <iostream>
#include <memory>

using namespace std;

class Foo
: public enable_shared_from_this<Foo>
{
public:
  shared_ptr<Foo> ptr(){
    return shared_from_this();
  }
};

int main()
{
  Foo f;
  auto ptr = f.ptr();
}
