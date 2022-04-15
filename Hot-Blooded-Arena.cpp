#include <iostream>
#include <map>
using namespace std;

int main() {
    int n;
    cin >> n;
    map<int, int> members;
    map<int, int, greater<int>> members_rev;
    members.insert({100'000'0000, 1});
    members_rev.insert({100'000'0000, 1});
    for (int i = 0; i < n; i++) {
        int id, s;
        cin >> id >> s;
        auto l = members_rev.upper_bound(s), h = members.upper_bound(s);
        if (l == members_rev.end())
            cout << id << ' ' << h->second << endl;
        else {
            auto [s_l, id_l] = *l;
            auto [s_h, id_h] = *h;
            if (s - s_l > s_h - s)
                cout << id << ' ' << id_h << endl;
            else
                cout << id << ' ' << id_l << endl;
        }
        members.insert({s, id});
        members_rev.insert({s, id});
    }
    return 0;
}