#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

set<int> hst;
multiset<int> st;

void op_add(int num) {
    st.insert(num);
    hst.insert(num);
    cout << st.count(num) << endl;
}

void op_del(int num) {
    int count = st.count(num);
    cout << count << endl;
    while (count--) st.erase(st.find(num));
}

void op_ask(int num) { cout << hst.count(num) << ' ' << st.count(num) << endl; }

int main() {
    int n;
    cin >> n;
    while (n--) {
        string op;
        cin >> op;
        if (op == "add") {
            int num;
            cin >> num;
            op_add(num);
        } else if (op == "del") {
            int num;
            cin >> num;
            op_del(num);
        } else if (op == "ask") {
            int num;
            cin >> num;
            op_ask(num);
        }
    }
    return 0;
}