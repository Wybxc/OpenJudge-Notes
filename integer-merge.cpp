#include <iostream>
// #include <bits/stdc++.h>
using namespace std;
unsigned int calc(unsigned int n, unsigned m, int x, int y) {
    constexpr unsigned int int_max = (unsigned int)-1;
    unsigned int mask = ((1 << x) - 1) | (int_max - (1 << (32 - y)) + 1);
    return (n & mask) | (m & ~mask);
}
int main() {
    int x, y, t;
    unsigned int n, m;
    cin >> t;
    while (t--) {
        cin >> n >> m >> x >> y;
        cout << calc(n, m, x, y) << endl;
    }
    return 0;
}