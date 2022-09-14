#include <iostream>
#include <memory>
#include <vector>
using namespace std;

template <typename Cmp>
class MonoQueue {
    unique_ptr<int[]> values;
    unique_ptr<int[]> indices;
    int head, tail;
    int window_size;
    Cmp cmp;

  public:
    MonoQueue(int window_size, Cmp cmp)
        : window_size(window_size),
          cmp(cmp),
          values(make_unique<int[]>(window_size + 10)),
          indices(make_unique<int[]>(window_size + 10)),
          head(0),
          tail(0) {}

    void push(int value, int index) {
        while (head < tail && cmp(value, values[tail - 1])) {
            tail--;
        }
        values[tail] = value;
        indices[tail] = index;
        tail++;
        while (head < tail && indices[head] <= index - window_size) {
            head++;
        }
    }
    int top() { return values[head]; }
};

int main() {
    int n, k;
    cin >> n >> k;
    auto min_queue = make_unique<MonoQueue<less<int>>>(k, less<int>());
    auto max_queue = make_unique<MonoQueue<greater<int>>>(k, greater<int>());
    vector<int> mins, maxs;
    for (int i = 0; i < k - 1; i++) {
        int a;
        cin >> a;
        min_queue->push(a, i);
        max_queue->push(a, i);
    }
    for (int i = k - 1; i < n; i++) {
        int a;
        cin >> a;
        min_queue->push(a, i);
        mins.push_back(min_queue->top());
        max_queue->push(a, i);
        maxs.push_back(max_queue->top());
    }
    for (auto m : mins) {
        cout << m << " ";
    }
    cout << endl;
    for (auto m : maxs) {
        cout << m << " ";
    }
    cout << endl;
    return 0;
}