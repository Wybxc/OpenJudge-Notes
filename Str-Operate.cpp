#include <iostream>
#include <optional>
#include <sstream>
#include <string>
using namespace std;

int str_num;
string strs[21];

optional<int> to_int(string str) {
    int result = 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] < '0' || str[i] > '9') return nullopt;
        result = result * 10 + str[i] - '0';
    }
    return result;
}

string get_str();

int get_int() {
    string cmd;
    cin >> cmd;
    if (cmd == "find") {
        string s = get_str();
        int n = get_int();
        int result = strs[n].find(s);
        if (result == string::npos) return s.size();
        return result;
    } else if (cmd == "rfind") {
        string s = get_str();
        int n = get_int();
        int result = strs[n].rfind(s);
        if (result == string::npos) return s.size();
        return result;
    }
    return stoi(cmd);
}

string get_str() {
    string cmd;
    cin >> cmd;
    if (cmd == "copy") {
        int n = get_int();
        int x = get_int();
        int l = get_int();
        return strs[n].substr(x, l);
    } else if (cmd == "add") {
        string s1 = get_str();
        string s2 = get_str();
        if (auto n1 = to_int(s1))
            if (0 <= *n1 && *n1 <= 99999)
                if (auto n2 = to_int(s2))
                    if (0 <= *n2 && *n2 <= 99999) return to_string(*n1 + *n2);
        return s1 + s2;
    }
    return cmd;
}

int main() {
    cin >> str_num;
    for (int i = 1; i <= str_num; i++) cin >> strs[i];
    string cmd;
    while (cin >> cmd) {
        if (cmd == "insert") {
            string s = get_str();
            int n = get_int();
            int x = get_int();
            strs[n].insert(x, s);
        } else if (cmd == "reset") {
            string s = get_str();
            int n = get_int();
            strs[n] = s;
        } else if (cmd == "print") {
            int n = get_int();
            cout << strs[n] << endl;
        } else if (cmd == "printall") {
            for (int i = 1; i <= str_num; i++) cout << strs[i] << endl;
        } else if (cmd == "over")
            break;
    }
    return 0;
}