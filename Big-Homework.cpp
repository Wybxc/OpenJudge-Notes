#include <iostream>
#include <string>
#include <vector>
using namespace std;

int N;
string names[20];
int ddl[20], esp[20];
constexpr int MAX = 1 << 16;
struct DP {
    int score{}, time{};
    string result;
} dp[MAX];  // dp[i][s] 表示选择前 i 门课，状态为 s
            // 时的最少扣分，及其对应的花费的时间
bool operator<(const DP& left, const DP& right) {
    if (left.score < right.score) return true;
    if (left.score > right.score) return false;
    return left.result < right.result;
}

// dp[i][s] = min({
//      let {score, time} = dp[i-1][s & ~(1<<k)];
//      struct DP {
//          score: score + calc(time + esp[k], ddl[k])
//          time: time + esp[k]
//      }
// } for k in 0..N-1 if !(s & (1<<k)))

int calc(int time, int d) { return time <= d ? 0 : time - d; }

int main() {
    int T;
    cin >> T;
    for (int _t = 1; _t <= T; _t++) {
        for (auto& name : names) name.clear();
        for (auto& d : ddl) d = 0;
        for (auto& e : esp) e = 0;
        for (auto& d : dp) {
            d.score = d.time = 0;
            d.result.clear();
        }
        cin >> N;
        for (int i = 0; i < N; i++) {
            cin >> names[i] >> ddl[i] >> esp[i];
        }
        int n_max = (1 << N) - 1;

        for (int s = 1; s <= n_max; s++) {  // 单调性：s & ~(1<<k) 小于 s
            DP m_min = {1000, 1000};
            for (int k = 0; k < N; k++) {
                int s_before = s & ~(1 << k);
                if (s != s_before) {
                    auto [score, time, result] = dp[s_before];
                    time += esp[k];
                    score += calc(time, ddl[k]);
                    DP m_new = {score, time, result + names[k] + "\n"};
                    if (m_new < m_min)
                        m_min = {score, time, result + names[k] + "\n"};
                }
            }
            dp[s] = m_min;
        }
        cout << dp[n_max].score << endl << dp[n_max].result;
    }
}
