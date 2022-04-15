#include <iostream>
using namespace std;

class MyCin {
  private:
    bool eof = false;

  public:
    MyCin& operator>>(int& dest) {
        if (!eof) {
            cin >> dest;
            if (dest == -1) eof = true;
        }
        return *this;
    }

    operator bool() { return !eof; }
};
int main() {
    MyCin m;
    int n1, n2;
    while (m >> n1 >> n2) cout << n1 << " " << n2 << endl;
    return 0;
}