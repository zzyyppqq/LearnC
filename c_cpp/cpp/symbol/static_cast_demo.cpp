//
// Created by 张宜鹏 on 2022/4/19.
//
#include <iostream>
#include <cstdlib>

using namespace std;

class Complex {
public:
    Complex(double real = 0.0, double imag = 0.0) : m_real(real), m_imag(imag) {}

public:
    operator double() const { return m_real; }  //类型转换函数
private:
    double m_real;
    double m_imag;
};

/**
 * static_cast 也不能用来去掉表达式的 const 修饰和 volatile 修饰。换句话说，不能将 const/volatile 类型转换为非 const/volatile 类型。
 * static_cast 是“静态转换”的意思，也就是在编译期间转换，转换失败的话会抛出一个编译错误
 */
void test_static_cast() {
    //下面是正确的用法
    int m = 100;
    Complex c(12.5, 23.8);
    long n = static_cast<long>(m);  //宽转换，没有信息丢失
    char ch = static_cast<char>(m);  //窄转换，可能会丢失信息
    int *p1 = static_cast<int *>( malloc(10 * sizeof(int)));  //将void指针转换为具体类型指针
    void *p2 = static_cast<void *>(p1);  //将具体类型指针，转换为void指针
    double real = static_cast<double>(c);  //调用类型转换函数

    //下面的用法是错误的
    // float *p3 = static_cast<float *>(p1);  //不能在两个具体类型的指针之间进行转换
    // p3 = static_cast<float *>(0X2DF9);  //不能将整数转换为指针类型
}

/**
 * const_cast 比较好理解，它用来去掉表达式的 const 修饰或 volatile 修饰。
 * 换句话说，const_cast 就是用来将 const/volatile 类型转换为非 const/volatile 类型。
 * @return
 */
int test_const_cast() {
    const int n = 100;
    int *p = const_cast<int *>(&n);
    *p = 234;
    cout << "n = " << n << endl;
    cout << "*p = " << *p << endl;
    return 0;
}

class A {
public:
    A(int a = 0, int b = 0) : m_a(a), m_b(b) {}

private:
    int m_a;
    int m_b;
};

/**
 * reinterpret 是“重新解释”的意思，顾名思义，reinterpret_cast 这种转换仅仅是对二进制位的重新解释，不会借助已有的转换规则对数据进行调整，非常简单粗暴，所以风险很高。
 * reinterpret_cast 可以认为是 static_cast 的一种补充，一些 static_cast 不能完成的转换，就可以用 reinterpret_cast 来完成，
 * 例如两个具体类型指针之间的转换、int 和指针之间的转换（有些编译器只允许 int 转指针，不允许反过来）
 * @return
 */
int test_reinterpret_cast() {
    //将 char* 转换为 float*
    char str[] = "http://c.biancheng.net";
    float *p1 = reinterpret_cast<float *>(str);
    cout << *p1 << endl;
    //将 int 转换为 int*
    int *p = reinterpret_cast<int *>(100);
    //将 A* 转换为 int*
    p = reinterpret_cast<int *>(new A(25, 96));
    cout << *p << endl;

    return 0;
}

class Base {
public:
    Base(int a = 0) : m_a(a) {}

    int get_a() const { return m_a; }

    virtual void func() const {}

protected:
    int m_a;
};

class Derived : public Base {
public:
    Derived(int a = 0, int b = 0) : Base(a), m_b(b) {}

    int get_b() const { return m_b; }

private:
    int m_b;
};

/**
 * dynamic_cast 用于在类的继承层次之间进行类型转换，它既允许向上转型（Upcasting），也允许向下转型（Downcasting）。
 * 向上转型是无条件的，不会进行任何检测，所以都能成功；
 * 向下转型的前提必须是安全的，要借助 RTTI 进行检测，所有只有一部分能成功。
 *
 * 向上转型（Upcasting）
 * @return
 */
int test_dynamic_cast_up() {
    //情况①
    Derived *pd1 = new Derived(35, 78);
    Base *pb1 = dynamic_cast<Derived *>(pd1);
    cout << "pd1 = " << pd1 << ", pb1 = " << pb1 << endl;
    cout << pb1->get_a() << endl;
    pb1->func();
    //情况②
    int n = 100;
    Derived *pd2 = reinterpret_cast<Derived *>(&n);
    Base *pb2 = dynamic_cast<Base *>(pd2);
    cout << "pd2 = " << pd2 << ", pb2 = " << pb2 << endl;
    cout << pb2->get_a() << endl;  //输出一个垃圾值
    pb2->func();  //内存错误
    return 0;
}

class A1 {
public:
    virtual void func() const { cout << "Class A" << endl; }

private:
    int m_a;
};

class B : public A1 {
public:
    virtual void func() const { cout << "Class B" << endl; }

private:
    int m_b;
};

class C : public B {
public:
    virtual void func() const { cout << "Class C" << endl; }

private:
    int m_c;
};

class D : public C {
public:
    virtual void func() const { cout << "Class D" << endl; }

private:
    int m_d;
};

int test_dynamic_cast_down() {
    A1 *pa = new A1();
    B *pb;
    C *pc;

    //情况①
    pb = dynamic_cast<B *>(pa);  //向下转型失败
    if (pb == NULL) {
        cout << "Downcasting failed: A* to B*" << endl;
    } else {
        cout << "Downcasting successfully: A* to B*" << endl;
        pb->func();
    }
    pc = dynamic_cast<C *>(pa);  //向下转型失败
    if (pc == NULL) {
        cout << "Downcasting failed: A* to C*" << endl;
    } else {
        cout << "Downcasting successfully: A* to C*" << endl;
        pc->func();
    }

    cout << "-------------------------" << endl;

    //情况②
    pa = new D();  //向上转型都是允许的
    pb = dynamic_cast<B *>(pa);  //向下转型成功
    if (pb == NULL) {
        cout << "Downcasting failed: A* to B*" << endl;
    } else {
        cout << "Downcasting successfully: A* to B*" << endl;
        pb->func();
    }
    pc = dynamic_cast<C *>(pa);  //向下转型成功
    if (pc == NULL) {
        cout << "Downcasting failed: A* to C*" << endl;
    } else {
        cout << "Downcasting successfully: A* to C*" << endl;
        pc->func();
    }

    return 0;
}

int main() {
    test_static_cast();
    test_const_cast();
    test_reinterpret_cast();
    test_dynamic_cast_down();
    test_dynamic_cast_up();
    return 0;
}
