#include <iostream>
using namespace std;

bool Greater2(int n1, int n2) { return n1 > n2; }
bool Greater1(int n1, int n2) { return n1 < n2; }
bool Greater3(double d1, double d2) { return d1 < d2; }

template <class T1, class T2>
void mysort(T1* start, T1* end, T2 comp) {
    if (start == end || start + 1 == end) return;
    auto left = start + 1, right = end - 1;
    while (left != right) {
        while (left != right && comp(*left, *start)) left++;
        while (left != right && !comp(*right, *start)) right--;
        if (left != right) swap(*left, *right);
    }
    if (comp(*left, *start)) swap(*left, *start);
    mysort(start, left, comp);
    mysort(left, end, comp);
}

#define NUM 5
int main() {
    int an[NUM] = {8, 123, 11, 10, 4};
    mysort(an, an + NUM, Greater1);  //从小到大排序
    for (int i = 0; i < NUM; i++) cout << an[i] << ",";
    mysort(an, an + NUM, Greater2);  //从大到小排序
    cout << endl;
    for (int i = 0; i < NUM; i++) cout << an[i] << ",";
    cout << endl;
    double d[6] = {1.4, 1.8, 3.2, 1.2, 3.1, 2.1};
    mysort(d + 1, d + 5, Greater3);  //将数组从下标1到下标4从小到大排序
    for (int i = 0; i < 6; i++) cout << d[i] << ",";
    return 0;
}