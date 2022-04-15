#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
const int MAX = 110;
class CHugeInt {
    int digits[210];

  public:
    CHugeInt(const CHugeInt& other) {
        memcpy(digits, other.digits, sizeof(digits));
    }
    CHugeInt(const char* s) {
        memset(digits, 0, sizeof(digits));
        int len = strlen(s);
        for (int i = 0; i < len; ++i) {
            digits[i] = s[len - i - 1] - '0';
        }
    }
    CHugeInt(int n) {
        memset(digits, 0, sizeof(digits));
        int len = 0;
        while (n) {
            digits[len++] = n % 10;
            n /= 10;
        }
    }
    CHugeInt& operator=(const CHugeInt& other) {
        if (this == &other) return *this;
        memcpy(digits, other.digits, sizeof(digits));
        return *this;
    }
    CHugeInt operator+(const CHugeInt& other) const {
        CHugeInt res{*this};
        int i = 0;
        while (i < 210) {
            res.digits[i] += other.digits[i];
            if (res.digits[i] >= 10) {
                res.digits[i + 1] += res.digits[i] / 10;
                res.digits[i] %= 10;
            }
            ++i;
        }
        while (i < 210 && res.digits[i] >= 10) {
            res.digits[i + 1] += res.digits[i] / 10;
            res.digits[i] %= 10;
            ++i;
        }
        return res;
    }
    CHugeInt operator+(int other) const {
        CHugeInt res{*this};
        int i = 0;
        res.digits[0] += other;
        while (i < 210 && res.digits[i] >= 10) {
            res.digits[i + 1] += res.digits[i] / 10;
            res.digits[i] %= 10;
            ++i;
        }
        return res;
    }
    CHugeInt& operator+=(int other) {
        int i = 0;
        digits[0] += other;
        while (i < 210 && digits[i] >= 10) {
            digits[i + 1] += digits[i] / 10;
            digits[i] %= 10;
            ++i;
        }
        return *this;
    }
    friend CHugeInt operator+(int left, const CHugeInt& right) {
        return right + left;
    }
    friend ostream& operator<<(ostream& os, const CHugeInt& num) {
        int i = 210;
        while (i > 0 && num.digits[i - 1] == 0) --i;
        if (i == 0)
            os << 0;
        else {
            while (i > 0) {
                os << num.digits[i - 1];
                --i;
            }
        }
        return os;
    }
    CHugeInt operator++(int) {
        CHugeInt res{*this};
        ++*this;
        return res;
    }
    CHugeInt& operator++() { return *this += 1; }
};
int main() {
    char s[210];
    int n;

    while (cin >> s >> n) {
        CHugeInt a(s);
        CHugeInt b(n);

        cout << a + b << endl;
        cout << n + a << endl;
        cout << a + n << endl;
        b += n;
        cout << ++b << endl;
        cout << b++ << endl;
        cout << b << endl;
    }
    return 0;
}