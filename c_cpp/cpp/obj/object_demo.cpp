//
// Created by 张宜鹏 on 2022/4/19.
//

#include <iostream>

using namespace std;

class Line {
public:
    static int count;

    int getLength(void);

    Line();             // 简单的构造函数
    Line(int len);             // 简单的构造函数
    Line(const Line &obj);      // 拷贝构造函数
    ~Line();                     // 析构函数
    friend void print(Line line); //友元函数
    friend void println(const Line &obj);

    virtual int area();// 虚函数
    static int getCount() {
        return count;
    }

    // 运算符重载
    Line operator+(const Line &line) {
        Line l;
        l.len = this->len + line.len;
        return l;
    }

private:
    int len;
    int *ptr;

    void test();
};

// 不是任何类的成员函数
void print(Line line) {
    // 因为 print() 是 Line 的友元，它可以直接访问该类的任何成员
    line.test();
    cout << "-->" << line.getLength() << endl;
}

void println(const Line &obj) {
    obj.ptr;
}

void test(Line line) {
    //line.test();
}

static int a = 0;

int Line::count = 0;
int b = Line::getCount();

Line::Line() {

}

// 成员函数定义，包括构造函数
Line::Line(int len) {
    cout << "调用构造函数" << endl;
    // 为指针分配内存
    ptr = new int;
    *ptr = len;
    count++;
}

// 拷贝构造函数
Line::Line(const Line &obj) {
    cout << "调用拷贝构造函数并为指针 ptr 分配内存" << endl;
    ptr = new int;
    *ptr = *obj.ptr; // 拷贝值
}

Line::~Line(void) {
    cout << "释放内存" << endl;
    delete ptr;
}

void Line::test() {

}

int Line::getLength(void) {
    return *ptr;
}

int Line::area() {

}

void display(Line obj) {
    cout << "line 大小 : " << obj.getLength() << endl;
}

// 程序的主函数
int main() {
    // 这里会调用拷贝构造函数
    Line line1(10);
    // 这里也调用了拷贝构造函数
    Line line2 = line1;

    display(line1);

    display(line2);

    Line line = Line(10);
    display(line);
    return 0;
}