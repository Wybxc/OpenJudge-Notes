#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <unordered_map>
using namespace std;

constexpr int MAXN = 1000'0000;

int primes[MAXN];
bool vis[MAXN] = {0};
void euler_prime(int n) {
    static int i = 2;
    static int cnt = 0;
    for (; i <= n; ++i) {
        if (!vis[i]) {
            primes[cnt++] = i;
            // cout << "Prime: " << i << endl;
            vis[i] = true;
        }
        for (int j = 0; j < cnt; ++j) {
            if (i * primes[j] > n) break;
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

int prime_factor_num(int n) {
    static unordered_map<int, int> prime_map;
    if (prime_map.count(n)) return prime_map[n];
    int count = 0;
    int num = n;
    for (int i = 0; i < MAXN; ++i) {
        int p = primes[i];
        if (num == p) break;
        if (n % p == 0) {
            ++count;
            do n /= p;
            while (n % p == 0);
        }
        if (n == 1) break;
    }
    prime_map.insert({num, count});
    cerr << num << ": " << count << endl;
    return count;
}

struct comp {
    bool operator()(int a, int b) const {
        int pa = prime_factor_num(a), pb = prime_factor_num(b);
        if (pa == pb) return a > b;
        return pa > pb;
    }
};

deque<int> nums;

int main() {
    // string filename = __FILE__;
    // ifstream fin(filename.substr(0, filename.find('.')) + ".txt");
    // auto cinbuf = cin.rdbuf();
    // cin.rdbuf(fin.rdbuf());
    // ofstream fout(filename.substr(0, filename.find('.')) + ".out");
    // auto coutbuf = cout.rdbuf();
    // cout.rdbuf(fout.rdbuf());

    int N;
    cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= 10; j++) {
            int n;
            cin >> n;
            euler_prime(n);
            nums.push_back(n);
        }
        sort(nums.begin(), nums.end(), comp());
        cout << nums.front() << ' ' << nums.back() << endl;
        nums.pop_back();
        nums.pop_front();
    }

    // cin.rdbuf(cinbuf);
    // cout.rdbuf(coutbuf);
    return 0;
}