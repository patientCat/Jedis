//c++ program
//design by >^.^<
//@date    2019-12-15 04:22:47
#include <iostream>
#include <memory>

using namespace std;

class Foo
{
public:
  static shared_ptr<Foo> Create()
  {
    shared_ptr<Foo> ptr(new Foo);
    return ptr;
  }

protected:
  Foo() = default;
};

int main()
{
  auto ptr = Foo::Create();
}
