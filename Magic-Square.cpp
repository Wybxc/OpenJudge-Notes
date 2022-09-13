#include <iostream>
using namespace std;

int sq[50][50] = {0};

int main() {
    int n;
    cin >> n;
    int m = 2 * n - 1;
    size_t i = 0, j = n - 1;
    for (int k = 1; k <= m * m; k++) {
        sq[i][j] = k;
        if (i == 0 && j == m - 1)
            i++;
        else {
            int ni = (i - 1 + m) % m;
            int nj = (j + 1 + m) % m;
            if (sq[ni][nj] == 0) {
                i = ni;
                j = nj;
            } else {
                i = (i + 1 + m) % m;
            }
        }
    }
    for (i = 0; i < m; i++) {
        for (j = 0; j < m; j++) cout << sq[i][j] << " ";
        cout << endl;
    }
    return 0;
}