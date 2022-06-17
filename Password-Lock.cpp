#include <iostream>
#include <tuple>
using namespace std;

size_t N = 0;

class Password {
    int p;
    explicit Password(int p) : p(p) {}

  public:
    explicit Password(const string& s) {
        p = 0;
        for (char c : s) p = p * 2 + c - '0';
    }

    static Password read() {
        string s;
        cin >> s;
        N = s.size();
        return Password{s};
    }

    bool operator==(const Password& other) const { return p == other.p; }
    bool operator<(const Password& other) const { return p < other.p; };
    int operator[](size_t i) const { return p & (1 << i); }

    void operate(int k) {
        p ^= 1 << (k - 1);
        p ^= 1 << k;
        p ^= 1 << (k + 1);
        p &= (1 << N) - 1;
    }

    Password change(int k) {
        Password res = *this;
        res.operate(k);
        return res;
    }
};

int solve(const Password& from, const Password& to) {
    Password cur = from;
    int res = 0;
    for (int i = 0; i < N - 1; i++) {
        if (cur[i] != to[i]) {
            cur.operate(i + 1);
            res++;
        }
    }
    if (cur == to) return res;
    return 10000;
}

int main() {
    auto from = Password::read(), to = Password::read();

    int res1 = solve(from, to);
    int res2 = solve(from.change(0), to) + 1;
    int res = min(res1, res2);
    if (res < 1000)
        cout << res << endl;
    else
        cout << "impossible" << endl;
    return 0;
}
