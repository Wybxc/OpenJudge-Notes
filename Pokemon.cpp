#include <deque>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Pokemon {
    using computer = unordered_set<string>;
    unordered_map<string, computer> computers;
    unordered_map<string, deque<string>> backpack;

  public:
    void push(const string& name, const string& pokemon) {
        auto& bp = backpack[name];
        bp.push_back(pokemon);
        if (bp.size() > 6) {
            computers[name].insert(bp.front());
            bp.pop_front();
        }
    }
    bool get(const string& name, const string& pokemon) {
        if (computers[name].count(pokemon)) {
            computers[name].erase(pokemon);
            return true;
        }
        return false;
    }
};

int main() {
    int T, N;
    cin >> T;
    for (int iter_T = 1; iter_T <= T; iter_T++) {
        cin >> N;
        Pokemon po;
        for (int iter_N = 1; iter_N <= N; iter_N++) {
            char op;
            string name, pokemon;
            cin >> op >> name >> pokemon;
            if (op == 'C') {
                po.push(name, pokemon);
            } else if (op == 'T') {
                bool succ = po.get(name, pokemon);
                if (succ) {
                    cout << "Success" << endl;
                    po.push(name, pokemon);
                } else {
                    cout << "Failed" << endl;
                }
            }
        }
    }
    return 0;
}