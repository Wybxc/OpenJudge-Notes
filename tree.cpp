#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> lines;
int li = 0;
string read() { return lines[li++]; }

vector<string> tree(char end) {
    vector<string> dirs;
    vector<string> files;
    string s;
    for (s = read(); s[0] != end; s = read()) {
        if (s[0] == 'd') {
            auto d = tree(']');
            dirs.push_back("|     " + s);
            for (auto &l : d) dirs.push_back("|     " + l);
        }
        if (s[0] == 'f') files.push_back(s);
    }
    sort(files.begin(), files.end());
    for (auto &f : files) dirs.push_back(f);
    return move(dirs);
}

int main() {
    int N = 0;
    string sv;
    while (cin >> sv) {
        if (sv[0] == '#') break;
        if (sv[0] == '*') N++;
        lines.push_back(sv);
    }
    for (int i = 1; i <= N; i++) {
        cout << "DATA SET " << i << ":" << endl;
        auto v = tree('*');
        cout << "ROOT" << endl;
        for (auto &s : v) cout << s << endl;
        cout << endl;
    }
    return 0;
}
