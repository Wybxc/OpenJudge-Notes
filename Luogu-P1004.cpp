#include <iostream>
using namespace std;

int N;
int mp[10][10] = {0};
int dp[10][10][10][10] = {0};

// dp[i][j][k][l] = map[i][j] + map[k][l] * ( i != k || j != l )
//                + max(dp[i-1][j][k-1][l], dp[i][j-1][k-1][l],
//                dp[i-1][j][k][l-1], dp[i][j-1][k][l-1])

int max(int a, int b, int c, int d) { return max(max(a, b), max(c, d)); }

int main() {
    cin >> N;
    for (int x, y, n; cin >> x >> y >> n, n;) {
        mp[x][y] = n;
    }

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            for (int k = 1; k <= N; k++)
                for (int l = 1; l <= i + j - k; l++) {
                    dp[i][j][k][l] =
                        mp[i][j] + mp[k][l] * (i != k || j != l) +
                        max(dp[i - 1][j][k - 1][l], dp[i][j - 1][k - 1][l],
                            dp[i - 1][j][k][l - 1], dp[i][j - 1][k][l - 1]);
                }
    cout << dp[N][N][N][N] << endl;

    return 0;
}