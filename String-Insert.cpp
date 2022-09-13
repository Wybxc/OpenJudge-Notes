#include <iostream>
using namespace std;

int main() {
    string str, substr;
    while (cin >> str >> substr) {
        size_t midx = 0;
        for (size_t i = 0; i < str.size(); ++i) {
            if (str[i] > str[midx]) midx = i;
        }
        str.insert(midx + 1, substr);
        cout << str << endl;
    }
    return 0;
}