#include <iostream>
using namespace std;

template <typename F, typename G, typename Arg>
auto combine(F f, G g) {
    return [f, g](Arg x) { return f(f(x) + g(x)); };
}

int main() {
    auto Square = [](double a) { return a * a; };
    auto Inc = [](double a) { return a + 1; };
    cout << combine<decltype(Square), decltype(Inc), int>(Square, Inc)(3)
         << endl;
    cout << combine<decltype(Inc), decltype(Square), double>(Inc, Square)(2.5)
         << endl;

    return 0;
}