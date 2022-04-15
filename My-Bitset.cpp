#include <cstring>
#include <iostream>

using namespace std;
template <int bitNum>
struct MyBitset {
    char a[bitNum / 8 + 1];
    MyBitset() { memset(a, 0, sizeof(a)); };
    void Set(int i, int v) {
        char& c = a[i / 8];
        int bp = i % 8;
        if (v)
            c |= (1 << bp);
        else
            c &= ~(1 << bp);
    }

    constexpr bool operator[](int i) const { return a[i / 8] & (1 << (i % 8)); }

    class reference {
        char& c;
        int bp;
        reference(char& c, int bp) : c(c), bp(bp) {}
        friend class MyBitset;

      public:
        operator bool() const { return c & (1 << bp); }
        reference& operator=(const reference& other) {
            if (other)
                c |= (1 << bp);
            else
                c &= ~(1 << bp);
            return *this;
        }
        reference& operator=(bool v) {
            if (v)
                c |= (1 << bp);
            else
                c &= ~(1 << bp);
            return *this;
        }
    };

    reference operator[](int i) { return reference{a[i / 8], i % 8}; }

    void Print() {
        for (int i = 0; i < bitNum; ++i) cout << (*this)[i];
        cout << endl;
    }
};

int main() {
    int n;
    int i, j, k, v;
    while (cin >> n) {
        MyBitset<20> bs;
        for (int i = 0; i < n; ++i) {
            int t;
            cin >> t;
            bs.Set(t, 1);
        }
        bs.Print();
        cin >> i >> j >> k >> v;
        bs[k] = v;
        bs[i] = bs[j] = bs[k];
        bs.Print();
        cin >> i >> j >> k >> v;
        bs[k] = v;
        (bs[i] = bs[j]) = bs[k];
        bs.Print();
    }
    return 0;
}