#include <iostream>
#include <set>
using namespace std;
// 在此处补充你的代码
class Rectangle {
  public:
    int a, b;
    int S, C;
    Rectangle(int _a, int _b) : a(_a), b(_b) {
        S = a * b;
        C = (a + b) * 2;
    }
    bool operator<(const Rectangle& r) const {
        if (S == r.S)
            return C > r.C;
        else
            return S > r.S;
    }
    friend ostream& operator<<(ostream& os, const Rectangle& r) {
        os << r.S << " " << r.C;
        return os;
    }
};
class Comp {
  public:
    bool operator()(const Rectangle& r1, const Rectangle& r2) const {
        if (r1.C == r2.C)
            return r1.S < r2.S;
        else
            return r1.C < r2.C;
    }
};
int main() {
    multiset<Rectangle> m1;
    multiset<Rectangle, Comp> m2;
    int n, a, b;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        m1.insert(Rectangle(a, b));
        m2.insert(Rectangle(a, b));
    }
    for (multiset<Rectangle>::iterator it = m1.begin(); it != m1.end(); it++) {
        cout << *it << endl;
    }
    cout << endl;
    for (multiset<Rectangle>::iterator it = m2.begin(); it != m2.end(); it++) {
        cout << *it << endl;
    }
    return 0;
}