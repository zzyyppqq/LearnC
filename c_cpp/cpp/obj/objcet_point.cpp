//
// Created by 张宜鹏 on 2022/4/19.
//

#include<iostream>

using namespace std;


class Info {

private:

    int iage;
    int iid;

    void print();

public:
    // 构造函数
    Info(void);
    // 使用初始化列表来初始化字段
    Info(int age, int id) : iage(age), iid(id) {
        cout << "Object is being created" << endl;
    }
    ~Info();  // 这是析构函数声明

    void msg();

};

Info::Info(void) {
    cout << "Object is being created" << endl;
}

Info::~Info() {
    cout << "Object is being delete" << endl;
}

/**
 * 成员函数可以定义在类定义内部，或者单独使用范围解析运算符 :: 来定义。
 * 在类定义中定义的成员函数把函数声明为内联的，即便没有使用 inline 标识符
 */
void Info::msg() {
    cout << "age = " << this->iage << "\t";
    cout << "id = " << this->iid << endl;
    print();
}

void Info::print() {

}


typedef struct Data {
    Data(int id, float math) : did{id}, dmath{math} {}

    float dmath;
    int did;
} data_;


int main() {
    Info line;
    line.msg();

    Info information = Info(30, 1);
    information.msg();
    Info *cpt;
    cpt = &information;
    cpt->msg();

    data_ d{1, 145};
    cout << "d.id = " << d.did << "\t";
    cout << "d.math = " << d.dmath << endl;

    data_ *spt;
    spt = &d;
    cout << "spt->id = " << spt->did << "\t";
    cout << "spt->math = " << spt->dmath << endl;

    return 0;
}

// result:
// age = 30        id = 1
// age = 30        id = 1
// d.id = 1        d.math = 145
// spt->id = 1     spt->math = 145