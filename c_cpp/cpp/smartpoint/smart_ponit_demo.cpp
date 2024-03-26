//
// Created by 张宜鹏 on 2022/5/19.
//

#include <iostream>
#include <memory>

using namespace std;

class Datas {

public:

    int vx;

    Datas() {
        cout << "data" << endl;
    }

    Datas(int x) : vx(x) {}

    void msg() {
        cout << "msg" << endl;
    }

    void print() {
        cout << "print" << endl;
    }

};


void test(int *pInt);
void test2(int &pInt);

typedef struct col {
    int cid;
    float cscore;

    col(int id, float score) : cid{id}, cscore{score} {}

} collection;


void pointType() {

    std::shared_ptr<int>() = std::make_shared<int>();
    std::unique_ptr<int>() = std::make_unique<int>();

}

void test() {
    // create class data instances;
    Datas a = Datas();

    Datas d = Datas(3);

    Datas *cpt = &d;

    d.msg();

    cpt->msg();

    std::unique_ptr<Datas> datas = std::make_unique<Datas>(4);
    datas->print();


    auto upw1(std::make_unique<Datas>());
    std::unique_ptr<Datas> upw2(new Datas);
    upw2->print();


    Datas *ddd = new Datas(5);
    delete ddd;
//    delete &d;
    // create struct col object

    collection c{1, 145.3};

    cout << c.cid << endl;

    cout << c.cscore << endl;


    collection *spt = &c;

    cout << spt->cid << endl;

    cout << spt->cscore << endl;
}

void remodel(std::string &str) {
    std::string *ps = new std::string(str);
    str = *ps;
    delete ps;
    return;
}


unique_ptr<string> demo(const char *s) {
    unique_ptr<string> temp(new string(s));
    std::cout << temp->c_str() << std::endl;
    return temp;
}


int main() {

    //test();
    // Mutex::Autolock _l(mStateLock);

    std::unique_ptr<double> ap(new double);

    shared_ptr<double> pd;
    double *p_reg = new double;
//    pd = p_reg;
    pd = shared_ptr<double>(p_reg);
//    shared_ptr<double> pshared = p_reg;
//    shared_ptr<double> pshared(p_reg);


    shared_ptr<string> ps(new string("I am zyp"));
    shared_ptr<string> vocation;
    vocation = ps;

    // 有的时候将一个智能指针赋值给另一个，并不会导致悬挂指针
    unique_ptr<string> ps2, ps3;
    ps2 = demo("Uniquely special");

    std::cout << ps2 << ", " << ps2->c_str() << std::endl;
    ps3 = move(ps2);
    std::cout << ps3 << ", " << ps3->c_str() << *ps3 << std::endl;

    int a = 10;
    int b = 10;
    int *p = &a;

    std::cout << a << ", " << p << ", " << *p << std::endl;

    test(&a);
    std::cout << "a: " << a << std::endl;
    test2(b);

    std::cout << "b: " << b << std::endl;

//    make_shared<>()
    return 0;
}

void test(int *p) {
    *p = 20;
}

void test2(int &p) {
    p = 1;
}
