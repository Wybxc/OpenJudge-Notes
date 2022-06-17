#include <cstring>
#include <iostream>
using namespace std;

using i64 = long long;

i64 mem[260][260];

i64 memdec(int n, int m);
i64 dec(int n, int m) {
    if (n < m || n <= 0 || m <= 0) return 0;
    if (m == 1 || n == m) return 1;
    return memdec(n - 2, m - 2) + memdec(n - m, m);
}

i64 memdec(int n, int m) {
    if (mem[n][m] >= 0) return mem[n][m];
    return mem[n][m] = dec(n, m);
}

int main() {
    memset(mem, -1, sizeof(mem));
    int n;
    for (cin >> n; n; cin >> n) {
        i64 s = 0;
        for (int i = 1; i <= n; i++) s += memdec(n, i);
        cout << n << " " << s << endl;
    }
}
