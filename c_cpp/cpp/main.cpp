#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

void print(std::string msg) {
    std::cout << msg << std::endl;
}

class User {
public:
    void draw();

private:
    int age;
};

void User::draw() {
    cout << "draw circle!" << endl;
}

int char_to_wchar(wchar_t *pDest, const char *pSrc) {
    int len;
    int ret;

    len = strlen(pSrc) + 1;

    if (len <= 1)
        return 0;

    ret = mbstowcs(pDest, pSrc, len);

    return ret;
}

int wchar_to_char(char *pDest, const wchar_t *pSrc) {
    int len;
    int ret;

    len = wcslen(pSrc) + 1;

    if (len <= 1)
        return 0;

    ret = wcstombs(pDest, pSrc, len * sizeof(wchar_t));

    return ret;
}

int count=0;
void fun () {
    printf("%d",::count);
}

int main() {
    fun();

    printf("before\n");
    static_assert("1","64位系统上不支持！");
    //__builtin_trap();
    printf("after\n");


    int x = 0;
    int aaa = 10;
    goto lol;
    x = 10;
    lol:
    x = 100;
    aaa = 100;

    string str1 = "runoob";
    string str2 = "google";
    string str = str1 + str2;
    cout << "Hello, World!" << endl;
    print(str);

    User *user = new User();
    std::cout << "--->" << user << std::endl;
    long user_id = (long) user;
    std::cout << "--->" << user_id << std::endl;
    User *user_1 = reinterpret_cast<User *>(user_id);
    user_1->draw();

    cout << "sizeof(size_t)=" << sizeof(size_t) << endl;

    // char类型的字符串以’\0’结尾,wchar_t类型的字符串以’\0\0’结尾
    wchar_t aa[] = L"ABCD";
    wchar_t *bb = L"EF";
    // wchar_t需要使用wcout输出
    wcout << aa << endl;
    char *ptr = (char *) aa;
    char cc[] = "ABCF";
    char *p = (char *) cc;


    char a[64] = "你好，世界";
    wchar_t b[64];
    char c[64];

    memset(b, 0x00, sizeof(b));
    memset(c, 0x00, sizeof(c));

    setlocale(LC_CTYPE, "zh_CN.utf8");

    char_to_wchar(b, a);
    wchar_to_char(c, b);

    printf("%s\n", c);


    cout << "npos: " <<  std::string::npos << endl;
    return 0;
}


