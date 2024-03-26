//
// Created by 张宜鹏 on 2022/9/18.
//

#include<iostream>

using namespace std;
int a = 10;
int b = 100;
int *q;

void func(int **p) { //2
    cout << "func:&p=" << &p << ",p=" << p << endl;
    *p = &b; //3
    cout << "func:&p=" << &p << ",p=" << p << endl;
}

void my_malloc(char **s) {
    *s = (char *) malloc(100);
}

/**
 * 这里只改了三个地方，变成传二级指针。我们再看:
 * 因为传了指针q的地址(二级指针**p)到函数,所以二级指针拷贝(拷贝的是p,一级指针中拷贝的是q所以才有问题),
 * （拷贝了指针但是指针内容也就是指针所指向的地址是不变的）所以它还是指向一级指针q(*p = q)。
 * 在这里无论拷贝多少次，它依然指向q，那么*p = &b;自然的就是 q = &b;了。
 */
int main() {
    cout << "&a=" << &a << ",&b=" << &b << ",&q=" << &q << endl;
    q = &a;
    cout << "*q=" << *q << ",q=" << q << ",&q=" << &q << endl;
    func(&q); //1
    cout << "*q=" << *q << ",q=" << q << ",&q=" << &q << endl;


    /**
     * 我们代码中以二级指针作为参数比较常见的是，定义了一个指针MyClass *ptr=NULL，
     * 在函数内对指针赋值*ptr=malloc(...)，函数结束后指针依然有效.
     * 这个时候就必须要用二级指针作为参数func(MyClass **p,...)
     *
     * 这里给指针p分配内存，do something,然后free(p),
     * 如果用一级指针，那么就相当于给一个p的拷贝s分配内存，p依然没分配内存，
     * 用二级指针之后，才对p分配了内存。
     */
    char *p = NULL;
    my_malloc(&p);
    //do something
    if (p) {
        free(p);
    }

    return 0;
}
