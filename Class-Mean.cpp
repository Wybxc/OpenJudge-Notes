#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;
class CMean {
    int& result;
    double result_f;
    int count = 0;

  public:
    CMean(int& _result) : result(_result), result_f(_result) {}
    void operator()(int v) {
        result_f = (result_f * count + v) / (count + 1);
        result = (int)result_f;
        ++count;
    }
};

int main(int argc, char* argv[]) {
    int v;
    int t;
    cin >> t;
    while (t--) {
        cin >> v;
        vector<int> vec;
        while (v) {
            vec.push_back(v);
            cin >> v;
        }
        int myAver = 0;
        for_each(vec.begin(), vec.end(), CMean(myAver));
        cout << myAver << endl;
    }
    return 0;
}