#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

int N, F;
int pies[10000];
const double esp = 5e-5;

int main() {
    cin >> N >> F;
    for (int i = 0; i < N; i++) cin >> pies[i];

    sort(pies, pies + N, greater());

    double lo = 0, hi = M_PI * pies[0] * pies[0];
    while (hi - lo > esp) {
        double mid = (lo + hi) / 2;
        int count = 0;
        for (int i = 0; i < N; i++)
            count += (int)(M_PI * pies[i] * pies[i] / mid);
        if (count >= F + 1)
            lo = mid;
        else
            hi = mid;
    }
    cout << fixed << setprecision(3) << lo << endl;

    return 0;
}
