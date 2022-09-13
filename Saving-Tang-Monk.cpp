#include <cstdint>
#include <iostream>
#include <queue>
#include <set>
using namespace std;

/*
 ___  __ _ _   _  ___  _ __   __ _ _ __ __ _
/ __|/ _` | | | |/ _ \| '_ \ / _` | '__/ _` |
\__ \ (_| | |_| | (_) | | | | (_| | | | (_| |
|___/\__,_|\__, |\___/|_| |_|\__,_|_|  \__,_|
            __/ |
           |___/
*/

int N, M;
int8_t tx, ty;
int rooms[110][110];

int8_t d[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
struct State {
    int8_t x, y;    // 8 bit * 2
    int8_t keys;    // 4 bit
    int8_t snakes;  // 5 bit
    int steps;

    int hash() const { return x << 24 | y << 16 | keys << 8 | snakes; }
};

struct Comp {
    bool operator()(const State& a, const State& b) const {  // A*
        // int ha = a.steps + abs(a.x - tx) + abs(a.y - ty);
        // int hb = b.steps + abs(b.x - tx) + abs(b.y - ty);
        int ha = a.steps;
        int hb = b.steps;
        return ha > hb;
    }
};

int main() {
    while (cin >> N >> M && (N != 0 || M != 0)) {
        int8_t x, y;
        int snk_cnt = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                char room;
                cin >> room;
                if (room == 'K')
                    x = i, y = j, rooms[i][j] = 0;
                else if (room == 'T')
                    tx = i, ty = j, rooms[i][j] = 0;
                else if (room == 'S')
                    rooms[i][j] = -(++snk_cnt);
                else if (room == '#')
                    rooms[i][j] = -100;
                else if (room == '.')
                    rooms[i][j] = 0;
                else
                    rooms[i][j] = room - '0';
            }
        }

        State init = {x, y, 0, 0, 0};

        queue<State> states;
        set<int> visited;

        states.push(init);
        visited.insert(init.hash());

        while (!states.empty()) {
            auto state = states.front();
            auto [x, y, keys, snakes, steps] = state;
            states.pop();

            if (x == tx && y == ty && keys == M) {
                cout << steps << endl;
                break;
            }

            if (-5 <= rooms[x][y] && rooms[x][y] < 0) {
                int8_t snake_mask = 1 << (-rooms[x][y] - 1);
                if (!(snakes & snake_mask)) {  // fight snake
                    states.push({x, y, keys,
                                 static_cast<int8_t>(snakes | snake_mask),
                                 steps + 1});
                    continue;
                }
            }

            int8_t new_key = rooms[x][y] == keys + 1;
            for (int i = 0; i < 4; i++) {
                int8_t nx = x + d[i][0];
                int8_t ny = y + d[i][1];
                if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
                if (rooms[nx][ny] == -100) continue;  // wall

                State next = {nx, ny, static_cast<int8_t>(keys + new_key),
                              snakes, steps + 1};

                int hash = next.hash();
                if (visited.count(hash)) continue;

                states.push(next);
                visited.insert(hash);
            }
        }
        if (states.empty()) cout << "impossible" << endl;
    }
    return 0;
}