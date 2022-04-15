#include <cstring>
#include <iostream>
using namespace std;

class Array2 {
    int* p;
    int x, y;

  public:
    Array2() {}
    Array2(int x, int y) : x(x), y(y) {
        p = new int[x * y];
        memset(p, 0, sizeof(int) * x * y);
    }
    ~Array2() {
        if (p) delete[] p;
    }
    Array2& operator=(const Array2& other) {
        if (p == other.p) return *this;
        if (p) delete[] p;
        x = other.x;
        y = other.y;
        p = new int[x * y];
        memcpy(p, other.p, sizeof(int) * x * y);
        return *this;
    }
    int* operator[](int i) { return &p[i * y]; }
    int& operator()(int i, int j) { return p[i * y + j]; }
};

int main() {
    Array2 a(3, 4);
    int i, j;
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 4; j++) a[i][j] = i * 4 + j;
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 4; j++) {
            cout << a(i, j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;
    b = a;
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 4; j++) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}