#include <iostream>
using namespace std;

int L, N, M;
int ds[50002];

bool check(int d) {
    int curr = 0, quota = M;
    while (curr <= N) {
        int next = curr + 1;
        while (next <= N + 1 && ds[next] - ds[curr] < d) {
            next++;
            quota--;
            if (quota < 0) return false;
        }
        curr = next;
    }
    return true;
}

int main() {
    cin >> L >> N >> M;
    ds[0] = 0;
    for (int i = 1; i <= N; i++) cin >> ds[i];
    ds[N + 1] = L;

    int lo = 0, hi = L + 1;
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
//        cout << lo << " " << hi << " " << mid << endl;
        if (check(mid))
            lo = mid;
        else
            hi = mid;
    }
    cout << lo << endl;
    return 0;
}
