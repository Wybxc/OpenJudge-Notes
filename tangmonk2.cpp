#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int INF = 99999999;

typedef struct {
    int S[50];
    int x, y, len;
} state;

int Map[105][105];
int n, m, kx, ky, tx, ty, s_num;
int dir[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};
bool vis[105][105];

void bfs() {
    state from;
    memset(from.S, 0, sizeof(from.S));
    from.x = kx, from.y = ky, from.len = 0;

    queue<state> fin;
    fin.push(from);

    while (!fin.empty()) {
        state x = fin.front();

        if (Map[x.x][x.y] == m + 1) break;

        fin.pop();

        memset(vis, 0, sizeof(vis));
        queue<state> q;
        q.push(x);
        while (!q.empty()) {
            state xx = q.front();
            q.pop();

            if (Map[xx.x][xx.y] == Map[x.x][x.y] + 1) {
                fin.push(xx);
                continue;
            }

            state y;
            for (int i = 0; i < 4; ++i) {
                y.x = xx.x + dir[i][0];
                y.y = xx.y + dir[i][1];

                for (int i = 0; i < s_num; ++i) y.S[i] = xx.S[i];

                if (y.x >= 1 && y.x <= n && y.y >= 1 && y.y <= n &&
                    !vis[y.x][y.y] && Map[y.x][y.y] != -1) {
                    vis[y.x][y.y] = true;
                    y.len = xx.len + 1;

                    if (Map[y.x][y.y] >= 20 && !xx.S[Map[y.x][y.y] - 20])
                        y.S[Map[y.x][y.y] - 20] = 1;

                    q.push(y);
                }
            }
        }
    }

    if (fin.empty()) {
        printf("impossible\n");
        return;
    }

    int Min = INF;
    while (!fin.empty()) {
        state a = fin.front();
        fin.pop();

        int ans = 0;
        for (int i = 0; i < s_num - 20; ++i) {
            if (a.S[i]) ++ans;
        }

        Min = min(Min, a.len + ans);
    }

    printf("%d\n", Min);
    return;
}

int main() {
    while (~scanf("%d%d", &n, &m) && (n + m)) {
        s_num = 20;

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                char c;
                scanf(" %c", &c);

                if (c <= '9' && c >= '1') Map[i][j] = c - '0';
                if (c == '.') Map[i][j] = 11;
                if (c == '#') Map[i][j] = -1;
                if (c == 'S') Map[i][j] = s_num++;
                if (c == 'K') Map[i][j] = 0;
                if (c == 'T') Map[i][j] = m + 1;

                if (!Map[i][j]) {
                    kx = i, ky = j;
                } else if (Map[i][j] == m + 1) {
                    tx = i, ty = j;
                }
            }
        }

        bfs();
    }

    return 0;
}