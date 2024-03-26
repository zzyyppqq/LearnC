//
// Created by 张宜鹏 on 2022/4/19.
//
#include <iostream>
#include <sstream>

using namespace std;

int main() {

    char site[7] = {'R', 'U', 'N', 'O', 'O', 'B', '\0'};

    cout << "菜鸟教程: ";
    cout << site << endl;

//    char* a = "hello";
//    char* b = "world";
//    strcpy(b, a);
//    cout << "strcpy( b, a) : " << b << endl;
//



    char str1[13] = "runoob";
    char str2[13] = "google";
    char str3[13];
    int len;

    // 复制 str1 到 str3
    strcpy(str3, str1);
    cout << "strcpy( str3, str1) : " << str3 << endl;

    // 连接 str1 和 str2
    strcat(str1, str2);
    cout << "strcat( str1, str2): " << str1 << endl;

    // 连接后，str1 的总长度
    len = strlen(str1);
    cout << "strlen(str1) : " << len << endl;

    const char str[] = "http://www.runoob.com";
    const char ch = '.';
    const char *ret;
    // strchr(s1, ch); 返回一个指针，指向字符串 s1 中字符 ch 的第一次出现的位置。
    ret = strchr(str, ch);

    // [.] 之后的字符串是 [.runoob.com]
    printf("[%c] 之后的字符串是 [%s]\n", ch, ret);
    cout << "ret : " << ret << endl;
    cout << "*ret: " << *ret << endl;
    cout << "&ret: " << &ret << endl;

    // strstr(s1, s2); 返回一个指针，指向字符串 s1 中字符串 s2 的第一次出现的位置
    const char haystack[20] = "RUNOOB";
    const char needle[10] = "NOOB";
    const char *ret1;

    ret1 = strstr(haystack, needle);

    printf("子字符串是： %s\n", ret1);


    char out[20];
    sprintf(out, "outyuv_%dx%d.yuv\n", 100, 200);
    printf(out);
    // c++中，如果是单纯的字符串拼接，肯定是string+，譬如：
    // string str=string（c字符串）+c字符串+字符串变量+...；
    string s1 = "ABC";
    s1 += "abc";
    string s2 = s1 + "DEF";
    cout << "s2: " << s2 << endl;
    // 如果有其他的数据类型拼接，则使用stringstream，譬如
    stringstream tmp;
    tmp << "aaa" << 5;
    string res = tmp.str();
    cout << "res--->: " << res << endl;

    string stmt = "123" "abc" "efg";
    cout << "stmt: " << stmt << endl;

    return 1;
}