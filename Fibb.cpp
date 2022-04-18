#include <iostream>
#include <iterator>
using namespace std;

template <class T1, class T2>
void Copy(T1 s, T1 e, T2 x) {
    for (; s != e; ++s, ++x) *x = *s;
}

class Fib {
    int n;

  public:
    Fib(int n) : n(n) {}
    bool operator!=(const Fib& other) const { return n != other.n; }
    Fib operator++() { return Fib(n++); }
    int operator*() const {
        static int fibb[1000] = {0, 1};
        static int p = 2;        
        for (; p <= n; ++p) 
            fibb[p] = fibb[p - 1] + fibb[p - 2];
        return fibb[n];
    }
};

int main() {
    while (true) {
        int n;
        cin >> n;
        if (n == 0) break;

        Fib f1(1), f2(n);
        ostream_iterator<int> it(cout, " ");
        Copy(f1, f2, it);
        cout << endl;
    }
    return 0;
}