#include <iostream>
using namespace std;

int R, C;
int heights[110][110];
int path[110][110];
int max_path = 0;
struct Point {
    int x, y;
} dirs[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

constexpr int INF = 100000;

int calc(int x, int y) {
    if (path[x][y] != -1) return path[x][y];
    path[x][y] = 1;
    for (auto& dir : dirs) {
        int nx = x + dir.x;
        int ny = y + dir.y;
        if (heights[x][y] > heights[nx][ny])
            path[x][y] = max(path[x][y], calc(nx, ny) + 1);
    }
    max_path = max(max_path, path[x][y]);
    return path[x][y];
}

int main() {
    cin >> R >> C;
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++) cin >> heights[i][j];
    for (int i = 0; i <= R + 1; i++) heights[i][0] = heights[i][C + 1] = INF;
    for (int i = 0; i <= C + 1; i++) heights[0][i] = heights[R + 1][i] = INF;
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++) path[i][j] = -1;
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++) calc(i, j);
    cout << max_path << endl;
    return 0;
}
