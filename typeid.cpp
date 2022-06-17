#include <iostream>
#include <typeinfo>
using namespace std;

template <typename T>
void test(T&& a) {
    auto& type = typeid(a);
    cout << type.name() << endl;
}

int main() {
    int A[100];
    test(A);      // A100_i (clang, gcc)  int [100]     (MSVC)
    test(1);      // i      (clang, gcc)  int           (MSVC)
    test(A[1]);   // i      (clang, gcc)  int           (MSVC)
    test(&A[1]);  // Pi     (clang, gcc)  int * __ptr64 (MSVC)
    return 0;
}