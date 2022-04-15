#include <cstring>
#include <iostream>
#include <string>
using namespace std;
class MyString {
    char* p;

  public:
    MyString(const char* s) {
        if (s) {
            p = new char[strlen(s) + 1];
            strcpy(p, s);
        } else
            p = NULL;
    }
    ~MyString() {
        if (p) delete[] p;
    }    
    MyString(const MyString& s) {
        if (s.p) {
            p = new char[strlen(s.p) + 1];
            strcpy(p, s.p);
        } else
            p = NULL;
    }
    MyString& Copy(const MyString& other) {
        return *this = other.p;
    }    
    MyString& operator=(const MyString& other) { return Copy(other); }
    MyString& operator=(const char* s) {
        if (s == p) return *this;
        if (s) {
            if (p) delete[] p;
            p = new char[strlen(s) + 1];
            strcpy(p, s);
        } else {
            if (p) delete[] p;
            p = NULL;
        }
        return *this;
    }
    operator char*() { return p; }
};
int main() {
    char w1[200], w2[100];
    while (cin >> w1 >> w2) {
        MyString s1(w1), s2 = s1;
        MyString s3(NULL);
        s3.Copy(w1);
        cout << s1 << "," << s2 << "," << s3 << endl;

        s2 = w2;
        s3 = s2;
        s1 = s3;
        cout << s1 << "," << s2 << "," << s3 << endl;
    }
}