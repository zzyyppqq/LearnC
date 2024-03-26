//
// Created by 张宜鹏 on 2022/4/19.
//

#include <iostream>
#include <exception>
#include <csignal>
#include <unistd.h>

using namespace std;

struct MyException : public exception {
    const char *what() const throw() {
        return "C++ Exception";
    }
};


double division(int a, int b) {
    if (b == 0) {
        throw "Division by zero condition!";
    }
    return (a / b);
}

void test() {
    try {
        throw MyException();
    } catch (MyException &e) {
        std::cout << "MyException caught" << std::endl;
        std::cout << e.what() << std::endl;
    } catch (std::exception &e) {
        //其他的错误
    }
}


void signalHandler(int signum) {
    cout << "---->Interrupt signal (" << signum << ") received.\n";

    // 清理并关闭
    // 终止程序

    exit(signum);

}

int main() {
    signal(SIGSEGV, signalHandler);
    try {
        MyException a;
        std::cout << a.what() << std::endl;
    } catch(std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    test();
    int x = 50;
    int y = 0;
    double z = 0;

    try {
        z = division(x, y);
        cout << z << endl;
    } catch (const char *msg) {
        cerr << msg << endl;
    }

    return 0;
}