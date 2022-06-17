#include <iostream>
#include <list>
#include <set>
#include <vector>

using namespace std;

template <class T>
void cmp(T&& a, int b) {
    if constexpr (is_same<T, int&>::value)
        printf("a\n");
    else if constexpr (is_same<T, int>::value)
        printf("b\n");
    else
        printf("c\n");
}

int main() {
    int A[100];
    A[0] = 1;
    A[1] = 2;
    cmp(A[0], 2);
    printf("finish 1\n");
    cmp(1, A[1]);
    printf("finish 2\n");
    cmp(A, A[1]);
    printf("finish 3\n");
}