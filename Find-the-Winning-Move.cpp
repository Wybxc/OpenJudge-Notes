#include <iostream>
#include <optional>
#include <tuple>
using namespace std;

char table[4][10];

optional<int> win();
int min_search(int alpha, int beta);
int max_search(int alpha, int beta);

tuple<int, int> alpha_beta() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (table[i][j] == '.') {
                table[i][j] = 'x';
                if (min_search(-100, 100)) return make_tuple(i, j);
                table[i][j] = '.';
            }

    return make_tuple(-1, -1);
}

int max_search(int alpha, int beta) {
    auto r = win();
    if (r.has_value()) return r.value();
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (table[i][j] == '.') {
                table[i][j] = 'x';
                alpha = max(min_search(alpha, beta), alpha);
                table[i][j] = '.';
                if (alpha >= beta) return alpha;
            }
    return alpha;
}

int min_search(int alpha, int beta) {
    auto r = win();
    if (r.has_value()) return r.value();
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (table[i][j] == '.') {
                table[i][j] = 'o';
                beta = min(max_search(alpha, beta), beta);
                table[i][j] = '.';
                if (alpha >= beta) return beta;
            }
    return beta;
}

optional<int> win() {
    for (int i = 0; i < 4; i++) {
        bool black = true;
        for (int j = 0; j < 4 && black; j++)
            black = black && table[i][j] == 'x';
        if (black) return 1;
        bool white = true;
        for (int j = 0; j < 4 && white; j++)
            white = white && table[i][j] == 'o';
        if (white) return -1;
    }

    for (int j = 0; j < 4; j++) {
        bool black = true;
        for (int i = 0; i < 4 && black; i++)
            black = black && table[i][j] == 'x';
        if (black) return 1;
        bool white = true;
        for (int i = 0; i < 4 && white; i++)
            white = white && table[i][j] == 'o';
        if (white) return -1;
    }

    bool black = true;
    for (int i = 0; i < 4 && black; i++) black = black && table[i][i] == 'x';
    if (black) return 1;
    bool white = true;
    for (int i = 0; i < 4 && white; i++) white = white && table[i][i] == 'o';
    if (white) return -1;

    black = true;
    for (int i = 0; i < 4 && black; i++)
        black = black && table[i][3 - i] == 'x';
    if (black) return 1;
    white = true;
    for (int i = 0; i < 4 && white; i++)
        white = white && table[i][3 - i] == 'o';
    if (white) return -1;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (table[i][j] == '.') return nullopt;
    return 0;
}

int main() {
    char flag[5];
    while (cin >> flag, flag[0] != '$') {
        for (int i = 0; i < 4; i++) {
            cin >> table[i];
        }
        auto [i, j] = alpha_beta();
        if (i >= 0)
            cout << '(' << i << ',' << j << ')' << endl;
        else
            cout << "#####\n";
    }
    return 0;
}