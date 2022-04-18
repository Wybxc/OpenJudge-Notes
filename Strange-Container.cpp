#include <iostream>
#include <string>
using namespace std;

template <class T>
class container {
    T value;

  public:
    container(T v) : value(v) {}
    container<T> operator+(const T& other) const { return value + other; }
    container<T> operator+(const container<T>& other) const {
        return value + other.value + other.value;
    }
    friend ostream& operator<<(ostream& os, const container<T>& c) {
        os << c.value;
        return os;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    string s1, s2;
    cin >> s1 >> s2;
    container<int> a = n;
    container<int> b = m;
    cout << a + b << endl;
    cout << a + m << endl;
    container<string> sa = string(s1);
    container<string> sb = string(s2);
    cout << sa + sb << endl;
    cout << sa + s2 << endl;
}