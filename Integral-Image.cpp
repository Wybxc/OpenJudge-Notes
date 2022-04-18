#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
class IntegralImage {
    int H, W;
    int** image;
    int lc = 0;

  public:
    IntegralImage(int H, int W) : H(H), W(W) {
        image = new int*[H];
        for (int i = 0; i < H; i++) {
            image[i] = new int[W];
        }
    }
    int* operator[](int i) { return image[i]; }
    void operator()(int* line) {
        image[lc][0] = line[0];
        for (int i = 1; i < W; i++) image[lc][i] = image[lc][i - 1] + line[i];
        if (lc > 0)
            for (int i = 0; i < W; i++) image[lc][i] += image[lc - 1][i];
        lc++;
    }
};

int main() {
    int H, W;
    cin >> H >> W;
    int** image = new int*[H];
    for (int i = 0; i < H; ++i) {
        image[i] = new int[W];
    }
    for (int i = 0; i < H; ++i)
        for (int j = 0; j < W; ++j) cin >> image[i][j];
    IntegralImage it(H, W);
    for_each(image, image + H, it);
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) cout << it[i][j] << " ";
        cout << endl;
    }
}