#include <cstdlib>
#include <iostream>
using namespace std;
int strlen(const char* s) {
    int i = 0;
    for (; s[i]; ++i)
        ;
    return i;
}
void strcpy(char* d, const char* s) {
    int i = 0;
    for (i = 0; s[i]; ++i) d[i] = s[i];
    d[i] = 0;
}
int strcmp(const char* s1, const char* s2) {
    for (int i = 0; s1[i] && s2[i]; ++i) {
        if (s1[i] < s2[i])
            return -1;
        else if (s1[i] > s2[i])
            return 1;
    }
    return 0;
}
void strcat(char* d, const char* s) {
    int len = strlen(d);
    strcpy(d + len, s);
}
class MyString {
  private:
    char* p = nullptr;
    MyString(const char* src, size_t len) {
        p = new char[len + 1];
        strcpy(p, src);
    }

  public:
    MyString() noexcept {}
    MyString(const char* s) {
        if (!s)
            p = nullptr;
        else {
            int len = strlen(s);
            p = new char[len + 1];
            strcpy(p, s);
        }
    }
    MyString(const MyString& s) {
        if (!s.p)
            p = nullptr;
        else {
            int len = strlen(s.p);
            p = new char[len + 1];
            strcpy(p, s.p);
        }
    }
    MyString(MyString&& s) noexcept {
        p = s.p;
        s.p = nullptr;
    }
    ~MyString() {
        if (p) delete[] p;
    }

    MyString& operator=(const MyString& s) {
        if (this == &s) return *this;
        if (p) delete[] p;
        if (!s.p)
            p = nullptr;
        else {
            int len = strlen(s.p);
            p = new char[len + 1];
            strcpy(p, s.p);
        }
        return *this;
    }
    MyString& operator=(MyString&& s) noexcept {
        if (this == &s) return *this;
        if (p) delete[] p;
        p = s.p;
        s.p = nullptr;
        return *this;
    }

    size_t length() const { return p ? strlen(p) : 0; }

    MyString& operator+=(const MyString& s) {
        int len = length() + s.length();
        char* tmp = new char[len + 1];
        strcpy(tmp, p);
        strcat(tmp, s.p);
        delete[] p;
        p = tmp;
        return *this;
    }
    MyString& operator+=(const char* s) {
        if (!s) return *this;
        int len = length() + strlen(s);
        char* tmp = new char[len + 1];
        strcpy(tmp, p);
        strcat(tmp, s);
        delete[] p;
        p = tmp;
        return *this;
    }

    friend auto& operator<<(ostream& os, const MyString& s) noexcept {
        if (s.p) os << s.p;
        return os;
    }

    bool operator<(const MyString& other) const {
        return strcmp(p, other.p) < 0;
    }
    bool operator>(const MyString& other) const {
        return strcmp(p, other.p) > 0;
    }
    bool operator<=(const MyString& other) const {
        return strcmp(p, other.p) <= 0;
    }
    bool operator>=(const MyString& other) const {
        return strcmp(p, other.p) >= 0;
    }
    bool operator==(const MyString& other) const {
        return strcmp(p, other.p) == 0;
    }
    bool operator!=(const MyString& other) const {
        return strcmp(p, other.p) != 0;
    }

    char& operator[](int i) noexcept { return p[i]; }
    const char& operator[](int i) const noexcept { return p[i]; }
    MyString operator()(int start, int len) const {
        char* tmp = new char[len + 1];
        for (size_t i = 0; i < len; ++i) tmp[i] = p[start + i];
        tmp[len] = 0;
        MyString result;
        result.p = tmp;
        return result;
    }

    template <typename T>
    MyString operator+(const T& other) const {
        MyString tmp = *this;
        tmp += other;
        return tmp;
    }
    friend MyString operator+(const char* left, const MyString& right) {
        if (!left) return right;
        int len = strlen(left) + right.length();
        MyString result(left, len);
        strcat(result.p, right.p);
        return result;
    }
};

int CompareString(const void* e1, const void* e2) {
    MyString* s1 = (MyString*)e1;
    MyString* s2 = (MyString*)e2;
    if (*s1 < *s2)
        return -1;
    else if (*s1 == *s2)
        return 0;
    else if (*s1 > *s2)
        return 1;
}
int main() {
    MyString s1("abcd-"), s2, s3("efgh-"), s4(s1);
    MyString SArray[4] = {"big", "me", "about", "take"};
    cout << "1. " << s1 << s2 << s3 << s4 << endl;
    s4 = s3;
    s3 = s1 + s3;
    cout << "2. " << s1 << endl;
    cout << "3. " << s2 << endl;
    cout << "4. " << s3 << endl;
    cout << "5. " << s4 << endl;
    cout << "6. " << s1[2] << endl;
    s2 = s1;
    s1 = "ijkl-";
    s1[2] = 'A';
    cout << "7. " << s2 << endl;
    cout << "8. " << s1 << endl;
    s1 += "mnop";
    cout << "9. " << s1 << endl;
    s4 = "qrst-" + s2;
    cout << "10. " << s4 << endl;
    s1 = s2 + s4 + " uvw " + "xyz";
    cout << "11. " << s1 << endl;
    qsort(SArray, 4, sizeof(MyString), CompareString);
    for (int i = 0; i < 4; i++) cout << SArray[i] << endl;
    // s1的从下标0开始长度为4的子串
    cout << s1(0, 4) << endl;
    // s1的从下标5开始长度为10的子串
    cout << s1(5, 10) << endl;
    return 0;
}