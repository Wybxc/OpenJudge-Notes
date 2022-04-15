#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
using namespace std;

double pop(stack<double>& st) {
    double res = st.top();
    st.pop();
    return res;
}

int main() {
    // ifstream fin("E:/PKU/OpenJudge/RPN-Calc.txt");
    // auto cinbuf = cin.rdbuf(fin.rdbuf());
    // cin.rdbuf(fin.rdbuf());
    int memsize;
    cin >> memsize;
    priority_queue<double, vector<double>, greater<double>> mem;
    for (int i = 0; i < memsize; i++) {
        double num;
        cin >> num;
        mem.push(num);
    }

    cout << setprecision(6) << scientific;

    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        stack<double> st;
        stringstream expr(line);
        string part;
        while (expr >> part) {
            if (part == "+") {
                double a = pop(st), b = pop(st);
                st.push(a + b);
            } else if (part == "-") {
                double a = pop(st), b = pop(st);
                st.push(b - a);
            } else if (part == "*") {
                double a = pop(st), b = pop(st);
                st.push(a * b);
            } else if (part == "/") {
                double a = pop(st), b = pop(st);
                st.push(b / a);
            } else if (part == "^") {
                double a = pop(st), b = pop(st);
                st.push(pow(b, a));
            } else if (part == "=") {
                double res = st.top();
                mem.pop();
                mem.push(res);
                cout << res << endl;
            } else {
                st.push(stod(part));
            }
        }
    }
    cout << endl;
    int i = 0;
    while (!mem.empty()) {
        cout << mem.top() << " ";
        mem.pop();
        if ((++i) % 10 == 0) cout << endl;
    }
    // cin.rdbuf(cinbuf);
    return 0;
}