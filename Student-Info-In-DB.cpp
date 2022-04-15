#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
using namespace std;

template <typename Key, typename Value, typename Compare = less<Key>>
class MyMultimap : public multimap<Key, Value, Compare> {
  private:
    using base = multimap<Key, Value, Compare>;
    class ppair : public pair<Key, Value> {
      public:
        friend ostream &operator<<(ostream &os, const ppair &p) {
            os << "(" << p.first << "," << p.second << ")";
            return os;
        }
    };

    using _iter = typename base::iterator;
 
  public:
    class iterator : public _iter {
      public:
        using _iter::_iter;
        iterator(const _iter &it) : _iter(it) {}
        iterator(_iter &&it) : _iter(move(it)) {}
        ppair &operator*() {
            auto &r = _iter::operator*();
            return reinterpret_cast<ppair &>(r);
        }
    };
    void Set(const Key &key, const Value &value) {
        for (auto [lower, upper] = this->equal_range(key); lower != upper;
             ++lower)
            lower->second = value;
    }
    iterator begin() { return iterator(base::begin()); }
    iterator end() { return iterator(base::end()); }
    iterator find(const Key &key) { return iterator(base::find(key)); }
};

struct Student {
    string name;
    int score;
};
template <class T>
void Print(T first, T last) {
    for (; first != last; ++first) cout << *first << ",";
    cout << endl;
}
int main() {
    Student s[] = {
        {"Tom", 80}, {"Jack", 70}, {"Jone", 90}, {"Tom", 70}, {"Alice", 100}};

    MyMultimap<string, int> mp;
    for (int i = 0; i < 5; ++i) mp.insert(make_pair(s[i].name, s[i].score));
    Print(mp.begin(), mp.end());  //按姓名从大到小输出

    mp.Set("Tom", 78);  //把所有名为"Tom"的学生的成绩都设置为78
    Print(mp.begin(), mp.end());

    MyMultimap<int, string, less<int>> mp2;
    for (int i = 0; i < 5; ++i) mp2.insert(make_pair(s[i].score, s[i].name));

    Print(mp2.begin(), mp2.end());  //按成绩从小到大输出
    mp2.Set(70, "Error");  //把所有成绩为70的学生，名字都改为"Error"
    Print(mp2.begin(), mp2.end());
    cout << "******" << endl;

    mp.clear();

    string name;
    string cmd;
    int score;
    while (cin >> cmd) {
        if (cmd == "A") {
            cin >> name >> score;
            if (mp.find(name) != mp.end()) {
                cout << "erroe" << endl;
            }
            mp.insert(make_pair(name, score));
        } else if (cmd == "Q") {
            cin >> name;
            MyMultimap<string, int>::iterator p = mp.find(name);
            if (p != mp.end()) {
                cout << p->second << endl;
            } else {
                cout << "Not Found" << endl;
            }
        }
    }
    return 0;
}