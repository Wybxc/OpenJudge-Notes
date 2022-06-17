#include <iostream>
#include <vector>
using namespace std;

string concat(const string& s1, const string& s2, int wd) {
    string s = s1;
    while (s.size() < wd) s += " ";
    s += s2;
    return s;
}

vector<string> fractal(int n) {
    if (n <= 0) return {};
    if (n == 1) return {R"( /\)", R"(/__\)"};
    vector<string> r;
    vector<string> v = fractal(n - 1);
    r.reserve(v.size() * 2);
    for (auto& s : v) r.push_back(concat("", s, 1 << (n - 1)));
    for (auto& s : v) r.push_back(concat(s, s, 1 << n));
    return r;
}

int main() {
    int n;
    while (cin >> n && n) {
        auto v = fractal(n);
        for (auto& s : v) cout << s << endl;
        cout << endl;
    }
}
