#include <iostream>
#include <string>
#include <tuple>
#include <map>
#include <vector>
using namespace std;

class BigInt {
  private:
    vector<int> v;  // 逆转，从低位到高位储存
    bool _inf;      // 是否是无穷大
    explicit BigInt(bool inf) : _inf(inf) {}

  public:
    BigInt() : _inf(false) {}
    static BigInt inf() { return BigInt(true); }
    explicit BigInt(const string& s) : _inf(false) {
        v.reserve(s.size());
        for (auto p = s.rbegin(); p != s.rend(); ++p) v.push_back(*p - '0');
    }
    explicit BigInt(vector<int> v) : v(move(v)), _inf(false) {}
    BigInt operator+(const BigInt& other) const {
        if (_inf || other._inf) return BigInt::inf();
        vector<int> res;
        res.reserve(max(v.size(), other.v.size()) + 1);
        int i = 0, overflow = 0;
        for (; i < v.size() && i < other.v.size(); i++) {
            res.push_back(v[i] + other.v[i] + overflow);
            overflow = res[i] / 10;
            res[i] %= 10;
        }
        for (; i < v.size(); i++) {
            res.push_back(v[i] + overflow);
            overflow = res[i] / 10;
            res[i] %= 10;
        }
        for (; i < other.v.size(); i++) {
            res.push_back(other.v[i] + overflow);
            overflow = res[i] / 10;
            res[i] %= 10;
        }
        while (overflow) {
            res.push_back(overflow % 10);
            overflow /= 10;
        }
        return BigInt(res);
    }
    bool operator<(const BigInt& other) const {
        if (_inf) return false;
        if (other._inf) return true;
        int i = (int)v.size() - 1, j = (int)other.v.size() - 1;
        while (i >= 0 && v[i] == 0) i--;
        while (j >= 0 && other.v[j] == 0) j--;
        if (i < 0 && j < 0) return false;
        if (i < j) return true;
        if (i > j) return false;
        for (int k = i; k > 0; k--) {
            if (v[k] < other.v[k]) return true;
            if (v[k] > other.v[k]) return false;
        }
        return false;
    }
    friend ostream& operator<<(ostream& os, const BigInt& bi) {
        if (bi._inf) return os << "inf";
        auto p = bi.v.rbegin();
        while (*p == 0 && p != bi.v.rend()) ++p;
        for (; p != bi.v.rend(); ++p) os << *p;
        return os;
    }
};

BigInt solve(const string& s, int m) {
    static map<tuple<string, int>, BigInt> hash;
    auto key = make_tuple(s, m);
    if (hash.count(key)) return hash[key];
    if (s.size() <= m) return BigInt::inf();
    if (m <= 0) return BigInt(s);
    BigInt res = BigInt::inf();
    for (auto i = 1; i < s.size(); i++) {
        auto left = BigInt(s.substr(0, i));
        auto right = solve(s.substr(i), m - 1);
        res = min(res, left + right);
    }
    hash[key] = res;
    return res;
}

int main() {
    int m;
    string expr;
    while (!cin.eof()) {
        cin >> m >> expr;
        cout << solve(expr, m) << endl;
    }
    return 0;
}
