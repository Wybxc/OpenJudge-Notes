#include <iostream>
#include <memory>
using namespace std;

class A {
  public:
    ~A() { cout << "des" << endl; }
};

int main() {
    shared_ptr<A> p{new A[2]};
    p.reset(new A[3]);
    return 0;
}