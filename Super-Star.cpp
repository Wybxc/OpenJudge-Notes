#include <cmath>
#include <cstdio>
#include <iostream>
#include <random>
using namespace std;

class Vec {
  public:
    double x, y, z;
    Vec() { x = y = z = 0; }
    Vec(double x, double y, double z) : x(x), y(y), z(z) {}
    Vec operator+(const Vec &v) const { return Vec(x + v.x, y + v.y, z + v.z); }
    Vec operator-(const Vec &v) const { return Vec(x - v.x, y - v.y, z - v.z); }
    Vec operator*(const double &k) const { return Vec(x * k, y * k, z * k); }
    Vec operator/(const double &k) const { return Vec(x / k, y / k, z / k); }
    Vec operator-() const { return Vec(-x, -y, -z); }
    double norm() const { return sqrt(x * x + y * y + z * z); }
};
auto &operator>>(istream &s, Vec &v) { return s >> v.x >> v.y >> v.z; }

Vec randv() {
    static mt19937_64 engine(0);
    static uniform_real_distribution<double> dist(0, 1);
    return Vec(dist(engine), dist(engine), dist(engine));
}

Vec p[40];

int main() {
    int N;
    while (cin >> N) {
        if (N == 0) break;
        for (int i = 0; i < N; i++) cin >> p[i];
        double min_dis = 200;
        Vec p0 = randv();
        for (double lr = 100; lr >= 1e-8; lr *= 0.98) {
            Vec g;
            double dis = 0;
            for (int i = 0; i < N; i++) {
                auto pi = p0 - p[i];
                double d = pi.norm();
                if (d > dis) {
                    dis = d;
                    g = -pi / d;
                }
            }
            p0 = p0 + g * lr;
            if (dis < min_dis) min_dis = dis;
        }
        printf("%.5lf\n", min_dis);
    }
    return 0;
}