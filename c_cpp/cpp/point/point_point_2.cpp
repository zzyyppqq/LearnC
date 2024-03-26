//
// Created by 张宜鹏 on 2023/2/2.
//

/// 在子函数中修改主函数传过来的指针的指向

#include <stdlib.h>
#include <time.h>
#include<stdio.h>
/*当然有必须使用二级指针才能解决的情况,如,某个函数的功能是
返回某个问题的计算结果,但是结果数据是不确定个数的值,所以
在调用此函数时不知道事先应分配多少空间来保存返回的数据,此时
的处理办法就是传递一个没有分配空间的指针的指针(地址)进去,
让函数自己根据计算的结果分配足够的空间来保存结果,并返回,
调用者使用了结果后,由调用者负责内存的释放,即,大家可能听说
过的"谁使用(调用)谁释放"之类的话,如下面的代码:*/

//返回不定结果个数的计算函数
//参数int **pResult  保存返回数据的指针的指针
//参数int &count     保存返回的结果个数
void Compute2(int **pResult, int &count) {
    //使用随机数来模拟计算结果数的个数
    srand(time(NULL));
    count = rand() % 10;//控制个数在10个以内

    *pResult = new int[count];//*pResult相当于主函数传来的pResult指针，
    //这里就修改了主函数中的pResult指向，因为还是指针，因此可以指向新开辟的空间
    for (int i = 0; i < count; i++) {
        (*pResult)[i] = rand();//给结果随即赋值
    }
}

//返回不定结果个数的计算函数(此函数不能返回数据)
//参数int *pResult   为保存返回数据的指针
//参数int &count     为保存返回的结果个数
void Compute1(int *pResult, int &count) {
    //使用随机数来模拟计算结果数的个数
    srand(time(NULL));
    count = rand() % 10;//控制个数在10个以内

    pResult = new int[count];
    for (int i = 0; i < count; i++) {
        pResult[i] = rand();//给结果随即赋值
    }
}

int main(void) {
    int *pResult = NULL;//待获取结果的指针，这里没有分配空间大小，因为不知道返回结果的个数
    //具体返回的个数在在子函数中确定，此时指针pResult指向也改变了
    //这就间接的说明“在子函数中修改主函数传来的指针”的意图
    //具体的应用就在于返回个数不确定的场景，这是后面编程的一个体会点
    int count = 0;//返回结果的个数

    /*
    Compute1(pResult,count);//pResult为指针,第二个参数使用引用传递,
    //使用这个函数时,在函数内部分配的内存的指针并没有返回到主函数中
    for ( int i = 0 ; i < count ; i++ )
    printf("第 %d 个结果为 : %d\n",pResult[i]);//执行了Compute1()函数后,pResult的值还是为NULL
    delete [] pResult;
    pResult = NULL;
    */

    Compute2(&pResult, count); //&pResult为指针的地址(即指针的指针),第二个参数使用引用传递
    for (int i = 0; i < count; i++)
        printf("第 %d 个结果为 : %d\n", i, pResult[i]);

    delete[] pResult;
    pResult = NULL;

    getchar();
    return 0;
}
