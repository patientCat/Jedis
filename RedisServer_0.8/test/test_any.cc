//c++ program
//design by >^.^<
//@date    2020-08-04 04:32:11
#include <iostream>
#include <any>

using namespace std;
class Test
{
  public:
    template <typename T>
    void setContext(T && v)
    {
      value_ = std::forward<T>(v);
    }

    any* value()
    {
      return &value_;
    }
  private:
    any value_;
};
int main()
{
    int x= 10;
   Test t;
  t.setContext(10); 
  int &y = any_cast<int &> (*t.value());
  cout << y << endl;
  y = 20;
}
