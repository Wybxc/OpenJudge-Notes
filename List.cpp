#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

using List = vector<int>;

unordered_map<int, List> map;

void op_new(int id) { map[id] = List(); }

void op_add(int id, int num) { map[id].push_back(num); }

void op_merge(int id1, int id2) {
    if (id1 == id2) return;
    List& l1 = map[id1];
    List& l2 = map[id2];
    l1.insert(l1.end(), l2.begin(), l2.end());
    map[id2] = List();
}

void op_unique(int id) {
    unordered_set<int> s;
    List& l = map[id];
    for (auto i : l) s.insert(i);
    l.clear();
    for (auto i : s) l.push_back(i);
}

void op_out(int id) {
    List& l = map[id];
    sort(l.begin(), l.end());
    for (auto i : l) cout << i << " ";
    cout << endl;
}

int main() {
    int n;
    cin >> n;
    while (n--) {
        string op;
        cin >> op;
        if (op == "new") {
            int id;
            cin >> id;
            op_new(id);
        } else if (op == "add") {
            int id, num;
            cin >> id >> num;
            op_add(id, num);
        } else if (op == "merge") {
            int id1, id2;
            cin >> id1 >> id2;
            op_merge(id1, id2);
        } else if (op == "unique") {
            int id;
            cin >> id;
            op_unique(id);
        } else if (op == "out") {
            int id;
            cin >> id;
            op_out(id);
        }
    }
    return 0;
}