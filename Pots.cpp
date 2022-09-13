#include <iostream>
#include <ostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;

enum class OP {
    FILL_1,
    FILL_2,
    DROP_1,
    DROP_2,
    POUR_12,
    POUR_21,
};
OP OPs[] = {OP::FILL_1, OP::FILL_2,  OP::DROP_1,
            OP::DROP_2, OP::POUR_12, OP::POUR_21};

ostream& operator<<(ostream& os, const OP& op) {
    switch (op) {
        case OP::FILL_1:
            os << "FILL(1)";
            break;
        case OP::FILL_2:
            os << "FILL(2)";
            break;
        case OP::DROP_1:
            os << "DROP(1)";
            break;
        case OP::DROP_2:
            os << "DROP(2)";
            break;
        case OP::POUR_12:
            os << "POUR(1,2)";
            break;
        case OP::POUR_21:
            os << "POUR(2,1)";
            break;
    }
    return os;
}

int A, B, C;

struct State {
    int a, b;
    vector<OP> ops;

    int hash() const { return a << 16 | b; }

    State deal(OP op) const {
        auto new_ops = ops;
        new_ops.push_back(op);

        if (op == OP::FILL_1) return {A, b, new_ops};
        if (op == OP::FILL_2) return {a, B, new_ops};
        if (op == OP::DROP_1) return {0, b, new_ops};
        if (op == OP::DROP_2) return {a, 0, new_ops};
        if (op == OP::POUR_12) {
            int sp = B - b;
            if (sp > a) return {0, a + b, new_ops};
            return {a - sp, B, new_ops};
        }
        if (op == OP::POUR_21) {
            int sp = A - a;
            if (sp > b) return {a + b, 0, new_ops};
            return {A, b - sp, new_ops};
        }

        return {};
    }
};

int main() {
    cin >> A >> B >> C;

    queue<State> q;
    set<int> visited;

    State init = {0, 0, {}};
    q.push(init);
    visited.insert(init.hash());

    while (!q.empty()) {
        auto state = q.front();
        q.pop();

        for (auto op : OPs) {
            auto new_state = state.deal(op);

            if (new_state.a < 0 || new_state.b < 0) continue;
            if (new_state.a > A || new_state.b > B) continue;
            if (visited.count(new_state.hash())) continue;

            if (new_state.a == C || new_state.b == C) {
                cout << new_state.ops.size() << endl;
                for (auto o : new_state.ops) cout << o << endl;
                return 0;
            }

            q.push(new_state);
            visited.insert(new_state.hash());
        }
    }
    if (q.empty()) cout << "impossible" << endl;

    return 0;
}