#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
using namespace std;

/*
E ::= F (('&' | '|') F)*
F ::= '(' E ')' | '!' F | 'V' | 'F'
 */

class Tokenizer {
  private:
    string s;
    int i;

  public:
    explicit Tokenizer(string s) noexcept : s(std::move(s)), i(0) {}
    char next() noexcept {
        for (; i < s.length();) {
            char c = s[i++];
            if (c != ' ') return c;
        }
        return '\0';
    }
    char peek() noexcept {
        for (; i < s.length(); i++) {
            char c = s[i];
            if (c != ' ') return c;
        }
        return '\0';
    }
    auto error(const string& message) noexcept {
        stringstream ss;
        ss << s << endl;
        for (int j = 0; j < i; j++) ss << ' ';
        ss << '^' << endl;
        ss << message << endl;
        return runtime_error(ss.str());
    }
};

bool in(char c, const string& s) {
    return any_of(s.begin(), s.end(), [c](char x) { return x == c; });
}

bool readE(Tokenizer&);
bool readF(Tokenizer&);

bool readE(Tokenizer& t) {
    bool a = readF(t);
    while (in(t.peek(), "&|")) {
        const char c = t.next();
        const bool b = readF(t);
        if (c == '&') a &= b;
        if (c == '|') a |= b;
    }
    return a;
}

bool readF(Tokenizer& t) {
    const char c = t.next();
    if (c == '(') {
        const bool a = readE(t);
        if (t.next() != ')') throw t.error("expected ')'");
        return a;
    }
    if (c == '!') return !readF(t);
    if (c == 'V') return true;
    if (c == 'F') return false;
    throw t.error("expected '(' or '!' or 'V' or 'F'");
}

int main() {
    string expr;
    for (int i = 1; getline(cin, expr); i++) {
        auto tokenizer = Tokenizer(expr);
        bool result = readE(tokenizer);
        cout << "Expression " << i << ": " << (result ? "V" : "F") << endl;
    }
    return 0;
}
