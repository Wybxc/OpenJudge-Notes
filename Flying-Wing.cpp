#include <iostream>
using namespace std;

int main() {
    int k;
    cin >> k;
    while (k--) {
        int n;
        cin >> n;
        int h[100];
        for (int i = 0; i < n; i++) cin >> h[i];
        int ans = 0;
        int dis[100];
        for (int i = 0; i < n; i++) dis[i] = 1;
        for (int i = n - 1; i >= 0; i--)
            for (int j = i - 1; j >= 0; j--)
                if (h[i] < h[j]) dis[j] = max(dis[j], dis[i] + 1);
        for (int i = 0; i < n; i++) ans = max(ans, dis[i]);
        for (int i = 0; i < n; i++) dis[i] = 1;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (h[i] < h[j]) dis[j] = max(dis[j], dis[i] + 1);
        for (int i = 0; i < n; i++) ans = max(ans, dis[i]);
        cout << ans << endl;
    }
}
