#include <iostream>
using namespace std;

int N, M;
int W[3412], D[3412];
int dp[12890] = {0};

// dp[0][0] = 0
// dp[i][j] = max(dp[i-1][j], dp[i-1][j-W[i]] + D[i])

int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) cin >> W[i] >> D[i];

    for (int i = 1; i <= N; i++) {
        for (int j = M; j >= W[i]; j--) {
            dp[j] = max(dp[j], dp[j - W[i]] + D[i]);
        }
    }

    cout << dp[M] << endl;
    return 0;
}
