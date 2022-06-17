#include <iostream>

using namespace std;

int a[9], b[9];

int tick(int i) {
    switch (i) {
        case 0:
            return a[0] + b[0] + b[1] + b[3];
        case 1:
            return a[1] + b[0] + b[1] + b[2] + b[4];
        case 2:
            return a[2] + b[1] + b[2] + b[5];
        case 3:
            return a[3] + b[0] + b[3] + b[4] + b[6];
        case 4:
            return a[4] + b[0] + b[2] + b[4] + b[6] + b[8];
        case 5:
            return a[5] + b[2] + b[4] + b[5] + b[8];
        case 6:
            return a[6] + b[3] + b[6] + b[7];
        case 7:
            return a[7] + b[4] + b[6] + b[7] + b[8];
        case 8:
            return a[8] + b[5] + b[7] + b[8];
        default:
            return 0;
    }
}

// bool loop(int t, int s = 0) noexcept {
//     if (t <= 0) {
//         for (int i = 0; i < 9; i++) {
//             int c = tick(i);
//             if (c % 4) return false;
//         }
//         return true;
//     }
//     if (5 <= s && s <= 8) {
//         int c = tick(s - 4);
//         if (c % 4) return false;
//     }
//     for (int i = s; i < 9; i++) {
//         b[i]++;
//         if (loop(t - 1, i)) return true;
//         b[i]--;
//     }
//     return false;
// }

void loop() {
    for (b[0] = 0; b[0] < 4; b[0]++)
        for (b[1] = 0; b[1] < 4; b[1]++)
            for (b[2] = 0; b[2] < 4; b[2]++)
                for (b[3] = 0; b[3] < 4; b[3]++)
                    for (b[4] = 0; b[4] < 4; b[4]++)
                        for (b[5] = 0; b[5] < 4; b[5]++)
                            for (b[6] = 0; b[6] < 4; b[6]++)
                                for (b[7] = 0; b[7] < 4; b[7]++)
                                    for (b[8] = 0; b[8] < 4; b[8]++) {
                                        bool r = true;
                                        for (int i = 0; i < 9 && r; i++) {
                                            int c = tick(i);
                                            if (c % 4) r = false;
                                        }
                                        if (r) return;
                                    }
}

int main() {
    for (int& i : a) cin >> i;
    for (int& i : b) i = 0;

    //    for (int total = 0;; total++) {
    //        bool r = loop(total);
    //        if (r) break;
    //    }

    loop();

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < b[i]; j++) cout << (i + 1) << ' ';
    cout << endl;
    return 0;
}
