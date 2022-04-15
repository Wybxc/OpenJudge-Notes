#include <cmath>
#include <iostream>
#include <random>
using namespace std;

constexpr double PI = 3.14159265358979323846;
int W, H, M;
int x[1001], y[1001];

/// [0,1) 内的随机数
double randf() {
    static mt19937_64 engine(0);
    static uniform_real_distribution<double> dist(0, 1);
    return dist(engine);
}
bool out(double x, int l, int h) { return x < l || x > h; }
double clip(double x, int l, int h) { return x < l ? l : (x > h ? h : x); }

void print(double x, double y) {
    int x10 = round(x * 10), y10 = round(y * 10);
    int x0 = x10 / 10, y0 = y10 / 10;
    int x1 = x10 % 10, y1 = y10 % 10;
    cout << "The safest point is (" << x0 << "." << x1 << ", " << y0 << "."
         << y1 << ")." << endl;
}

double value(double x0, double y0) {
    double result = sqrt(W * W + H * H);
    for (int i = 0; i < M; i++) {
        double xi = x0 - x[i], yi = y0 - y[i];
        double dis = sqrt(xi * xi + yi * yi);
        if (dis < result) result = dis;
    }
    return result;
}

int main() {
    int N;
    cin >> N;
    while (N--) {
        cin >> W >> H >> M;
        for (int i = 0; i < M; i++) {
            cin >> x[i] >> y[i];
        }

        double xm = 0, ym = 0;
        double max_dis = value(xm, ym);
        for (int k = 0; k < 30; k++) {
            double x0 = randf() * W, y0 = randf() * H;
            constexpr int D = 8;
            for (double lr = min(W, H); lr >= 1e-6; lr *= 0.9) {
                double m_dis = value(x0, y0);
                for (int i = 0; i < D; i++) {
                    double angle = i * 2 * PI / D;
                    double dx = lr * cos(angle);
                    double dy = lr * sin(angle);
                    if (out(x0 + dx, 0, W) || out(y0 + dy, 0, H)) continue;
                    double n_dis = value(x0 + dx, y0 + dy);
                    if (n_dis > m_dis) {
                        x0 += dx;
                        y0 += dy;
                        m_dis = n_dis;
                        break;
                    }
                }
            }
            double dis = value(x0, y0);
            if (dis > max_dis) {
                max_dis = dis;
                xm = x0;
                ym = y0;
            }
        }
        print(xm, ym);
    }
}