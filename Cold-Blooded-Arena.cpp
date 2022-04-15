#include <fstream>
#include <iostream>
#include <map>
#include <queue>
using namespace std;

using mlist = priority_queue<int, vector<int>, greater<int>>;
map<int, mlist> members;

auto& lookup(int s) {
    if (members.find(s) == members.end()) members.insert({s, mlist()});
    return members[s];
}

void add(int id, int s) { lookup(s).push(id); }

int main() {
    // string filename = __FILE__;
    // ifstream fin(filename.substr(0, filename.find('.')) + ".txt");
    // auto cinbuf = cin.rdbuf();
    // cin.rdbuf(fin.rdbuf());

    int n;
    cin >> n;
    add(1, 100'000'0000);
    for (int i = 0; i < n; i++) {
        int id, s;
        cin >> id >> s;
        auto h = members.upper_bound(s);
        auto l = h;
        if (l == members.begin())
            cout << id << ' ' << h->second.top() << endl;
        else {
            --l;
            auto [s_l, id_l] = *l;
            auto [s_h, id_h] = *h;
            if (s - s_l > s_h - s)
                cout << id << ' ' << id_h.top() << endl;
            else if (s - s_l == s_h - s)
                cout << id << ' ' << min(id_h.top(), id_l.top()) << endl;
            else
                cout << id << ' ' << id_l.top() << endl;
        }
        add(id, s);
    }

    // cin.rdbuf(cinbuf);
    return 0;
}