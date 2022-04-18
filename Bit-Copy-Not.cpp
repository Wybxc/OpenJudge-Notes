#include <iostream>
using namespace std;

int main() {
    int a, b, i, j;
    cin >> a >> b >> i >> j;
    int mask = ((1 << (j + 1)) - 1) & ~((1 << i) - 1);
    cout << ((a & ~mask) | (~b & mask)) << endl;
    return 0;
}