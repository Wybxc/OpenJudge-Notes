#include <iostream>
using namespace std;

template <typename Left, typename Right>
auto f(const Left &left) {
    return [left](const Right &right) { return left + right; };
}

int main() {
    cout << f<int, int>(7)(9) << endl;                      // 16
    cout << f<string, string>(" hello!")("world") << endl;  // world hello!
    cout << f<char, string>('!')("world") << endl;          // world!

    return 0;
}