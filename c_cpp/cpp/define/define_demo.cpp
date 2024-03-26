//
// Created by 张宜鹏 on 2022/4/19.
//

#include <iostream>

using namespace std;

#define PI 3.14159
#define MIN(a, b) (a<b ? a : b)
#define MKSTR(x) #x
#define concat(a, b) a ## b

#define DEBUG

#define MIN(a, b) (((a)<(b)) ? a : b)


//  gcc -E define_demo.cpp > test.p
int main() {
    cout << MKSTR(HELLO C++) << endl; // "HELLO C++"
    int xy = 100;
    cout << concat(x, y) << endl; // xy
    cout << "Value of PI :" << PI << endl;
    MIN(3, 4);

    int i, j;
    i = 100;
    j = 30;
#ifdef DEBUG
    cerr << "Trace: Inside main function" << endl;
#endif

#if 0
    /* 这是注释部分 */
   cout << MKSTR(HELLO C++) << endl;
#endif

    cout << "The minimum is " << MIN(i, j) << endl;

#ifdef DEBUG
    cerr << "Trace: Coming out of main function" << endl;
#endif


    cout << "Value of __LINE__ : " << __LINE__ << endl;
    cout << "Value of __FILE__ : " << __FILE__ << endl;
    cout << "Value of __DATE__ : " << __DATE__ << endl;
    cout << "Value of __TIME__ : " << __TIME__ << endl;
    return 0;
}