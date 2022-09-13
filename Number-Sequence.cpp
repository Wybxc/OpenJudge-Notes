#include <iostream>
using namespace std;

int length_k(int k) {
    if (k <= 0) return 0;
    if (k < 10) return 1;
    if (k < 100) return 2;
    if (k < 1000) return 3;
    if (k < 10000) return 4;
    if (k < 100000) return 5;
    return 1 + length_k(k / 10);
}

int length_sk(int k) {
    if (k <= 0) return 0;
    if (k < 10) return k;
    if (k < 100) return 9 + (k - 9) * 2;
    if (k < 1000) return 189 + (k - 99) * 3;
    if (k < 10000) return 2889 + (k - 999) * 4;
    if (k < 100000) return 38889 + (k - 9999) * 5;
    return length_k(k) + length_sk(k - 1);
}

long long sum_length_sk(long k) {
    if (k <= 0) return 0;
    if (k < 10) return k * (k + 1) / 2;
    if (k < 100) return 45 + (k - 9) * 9 + (k - 9) * (k - 9 + 1) / 2 * 2;
    if (k < 1000)
        return 9045 + (k - 99) * 189 + (k - 99) * (k - 99 + 1) / 2 * 3;
    if (k < 10000)
        return 1395495 + (k - 999) * 2889 + (k - 999) * (k - 999 + 1) / 2 * 4;
    if (k < 100000)
        return 189414495 + (k - 9999) * 38889 +
               (k - 9999) * (k - 9999 + 1) / 2 * 5;
    return length_sk(k) + sum_length_sk(k - 1);
}

int main() {    
    // cout << sum_length_sk(100000) << endl;
    int K;
    cin >> K;
    while (K--) {
        long long n;
        cin >> n;
        int i = 1;
        while (n > sum_length_sk(i)) i++;
        n -= sum_length_sk(i - 1);
        int j = 1;
        while (n > length_sk(j)) j++;
        n -= length_sk(j - 1);
        int k = 1;
        // while (n > length_k(k)) k++;
        // n -= length_k(k - 1);
        cout << to_string(j)[n - 1] << endl;
    }
}