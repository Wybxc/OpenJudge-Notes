#include <cmath>
#include <iostream>
using namespace std;

int x[101], y[101];

double clip(double x) { return x < -10000 ? -10000 : (x > 10000 ? 10000 : x); }

int main() {
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> x[i] >> y[i];
    }
    double x0 = 0, y0 = 0;
    double lr = 5000;
    double esp = 0.0001;
    int k = 1;
    while (k++) {
        double dx = 0, dy = 0;
        for (int i = 0; i < N; i++) {
            double xi = x0 - x[i], yi = y0 - y[i];
            if (xi || yi) {
                dx -= xi / sqrt(xi * xi + yi * yi) * lr;
                dy -= yi / sqrt(xi * xi + yi * yi) * lr;
            }
        }
        double ddx = clip(dx), ddy = clip(dy);
        if (abs(ddx) < esp && abs(ddy) < esp) break;
        x0 += ddx;
        y0 += ddy;
        lr /= 1.5;
        if (lr < 1) lr = 1;
    }
    double length = 0;
    for (int i = 0; i < N; i++) {
        length += sqrt((x0 - x[i]) * (x0 - x[i]) + (y0 - y[i]) * (y0 - y[i]));
    }
    // cout << x0 << " " << y0 << " " << k << endl;
    cout << (int)round(length) << endl;
    return 0;
}