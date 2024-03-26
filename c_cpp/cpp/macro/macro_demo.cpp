//
// Created by 张宜鹏 on 2022/5/13.
//

#include <iostream>
#include <string>

/**
 * 1. 宏是简单的符号替换，不会检查参数类型，而函数会严格检查输入的参数类型
 * 2. 因为宏是在编译期进行的符号替换，所以在运行时，不会带来额外的时间和空间开销，而函数会在运行时执行压栈出栈的操作，存在函数调用的开销
 * 3. 宏是不可以调试的，而函数可以进行单步调试
 * 4. 宏不支持递归，函数支持递归
 */


// -------------------- 定义 ---------------------------------

// 定义圆周率
#define PI 3.14
// 定义一个空指针
//#define NULL ((*void)0)
// 定义一个宏的名字为 SYSTEM_API，但是没有值
#define SYSTEM_API

class SYSTEM_API CSystem;

class CSystem;

// -------------------- 参数 ---------------------------------

#define MUL(x, y) x * y
#define MUL2(x, y) ((x) * (y))

// -------------------- 符号#和## ---------------------------------

// #符号把一个宏参数直接转换为字符串
#define STRING(x) #x
const char *str = STRING(test);
// str的内容就是"test"

// ##符号会连接两边的值，像一个粘合剂一样，将前后两部分粘合起来，从而产生一个新的值
#define VAR(index) INT_##index
int VAR(1);
// 宏被展开后将成为 int INT_1;

// -------------------- 可变参数 ---------------------------------

// 宏也可以支持可变长参数，这个特性可以用来对类似printf这样的函数进行封装，
// 使用时，使用__VA_ARGS__这个系统预定义宏来代替printf的参数，例如
// 至于为什么要在__VA_ARGS__之前添加##符号，主要是因为，如果不添加的话，
// 当只有fmt参数，__VA_ARGS__为空时，之前的逗号不会删除，从而导致编译错误，
// 而加上##符号的话，将使预处理器去除掉它前面的那个逗号。
#define trace(fmt, ...) printf(fmt, ##__VA_ARGS__)
// 这样我们就可以使用我们自己定义的宏 trace 来打印日志了
// error： trace("got a number");   ==>  trace("got a number",);

// -------------------- 多行的宏 ---------------------------------

#define ADD(x, y) do { int sum = (x) + (y); return sum; } while (0)
// 宏的内容比较长，也没有缩进，易读性较差，因此转为多行
#define ADD2(x, y) \
do \
{\
    int sum = (x) + (y);\
    return sum;\
} while (0)


// -------------------- 取消宏定义 ---------------------------------
#undef ADD2

// -------------------- 编译器参数定义以及预定义宏 ---------------------------------

/**
 *  宏	        类型	            含义
 * _FILE_	    const char *	当前所编译的文件名称(绝对路径)
 * _LINE_	    int	            当前所在的行号
 * _FUNCTION_	const char *	当前所在的函数名称
 * _DATE_	    const char *	当前的日期
 * _TIME_	    const char *	当前的时间
*/

// --------------- 宏的调试 ---------------------------------

// 宏不支持在运行时调试，但如果宏太过于复杂的话，出错也是难免的，因此，可以利用宏自身的特性把宏展开后的内容打印出来，来方便我们查错。
#pragma message ("will print this message")

#define SOMEMACRO 123456
#define MACROTOSTR2(x) #x
#define PRINTMACRO(x) #x " = " MACROTOSTR2(x)
#pragma message(PRINTMACRO(SOMEMACRO))

#define SOMEMACRO 123456
#define MACROPARAM(x) new int(x);
#define MACROTOSTR2(x) #x
#define PRINTMACRO(x) #x " = " MACROTOSTR2(x)
#pragma message(PRINTMACRO(MACROPARAM(SOMEMACRO)))


// --------------- 和#ifdef和#if等预处理指令配合 ---------------

// 通过和预处理指令配合，达到一定的代码开关控制，常见的比如在跨平台开发时，对不同的操作系统启用不同的代码。
#ifdef _WIN32 // 查看是否定义了该宏，Windows默认会定义该宏
// 如果是Windows系统则会编译此段代码
OutputDebugString("this is a Windows log");
#else
// 如果是mac，则会编译此段代码
//NSLog(@"this is a mac log");

#endif

// --------------- 如果要查看多个宏是否定义过，可使用下面的预处理指令 ---------------
#if defined(_WIN32) || defined(WIN32)
// 如果是Windows系统则会编译此段代码
OutputDebugString("this is a Windows log");
#endif

#define ENABLE_LOG 1
#if ENABLE_LOG
// trace("when enabled then print this log")
#endif


// --------------- 防止重复包含头文件 ---------------

#ifndef __SYSTEM_API_H__
#define __SYSTEM_API_H__
// 头文件的内容
#endif


// --------------- 打印错误信息 ---------------

// printf("%s %d printf message %s\n", __FILE__, __LINE__, "some reason");

#define trace(fmt, ...) printf("%s:%d#%s(): " fmt, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

// --------------- 减少重复代码 ---------------
// 如果有一个类，它携带有很多的属性，而每一个属性都必须进行实现set和get函数，那么就可以使用宏来减少代码的输入


// 类Widget拥有非常多的属性，但每一个属性的相应函数实现是类似的
class Widget {
private:
    int _Width;
    int _Height;
public:
    // Width属性
    int getWidth() const {
        return _Width;
    }

    void setWidth(int Width) {
        // 当设置新值时，打印一条日志，方便调试
        printf("setWidth %d\n", Width);
        _Width = Width;
    }

    // Height属性
    int getHeight() const {
        return _Height;
    }

    void setHeight(int Height) {
        // 当设置新值时，打印一条日志，方便调试
        printf("setHeight %d\n", Height);
        _Height = Height;
    }
    // 之后还有其他的属性定义......
};


// 定义一个PROPERTY宏来生成相应的函数实现
#define PROPERTY(Name)\
int get##Name() const\
{\
    return _##Name;\
}\
void set##Name()\
{\
    printf("set"#Name" %d\n", Name);\
    _##Name = Name;\
}

// 接下来就可以重新定义Widget类了
class Widget2 {
private:
    int _Width;
    int _Height;
public:
    // Width属性
    //PROPERTY(_Width)
    // Height属性
    //PROPERTY(_Height)
};



#ifndef NULL
#include <sys/_types.h> /* __DARWIN_NULL */
#define NULL  __DARWIN_NULL
#endif  /* NULL */

#ifndef APIENTRY
#define APIENTRY
#endif

#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif


#define GLAPI extern

typedef void (APIENTRYP PFNGLBUFFERDATAPROC)(int target);
GLAPI PFNGLBUFFERDATAPROC glad_glBufferData;
#define glBufferData glad_glBufferData

PFNGLBUFFERDATAPROC glad_glBufferData = NULL;

void test(char* s) {
    trace("printf message %s\n", s);
}

int main() {
    // glad_glBufferData = (PFNGLBUFFERDATAPROC)load("glBufferData");

    int a = PI;
    // ==> int ret = 2 * 3;
    int ret = MUL(2, 3);
    int ret2 = MUL2(2 + 3, 4);

    trace("got a number %d\n", 34);


    // ADD(1,2);
    // 取消宏定义，此宏报错
    // ADD2(1,2);

    // 利用“__DATE__”和“__TIME__”宏可以用来确定程序编译的时间
    printf("Compiled on %s at %s\n", __DATE__, __TIME__);

    // 编译器参数定义以及预定义宏
    std::cout << "__FILE__ : " << __FILE__ << std::endl;
    std::cout << "__FILE_NAME__ : " << __FILE_NAME__ << std::endl;
    std::cout << "__LINE__ : " << __LINE__ << std::endl;
    std::cout << "__STDC__ : " << __STDC__ << std::endl;
    std::cout << "__FUNCTION__ : " << __FUNCTION__ << std::endl;

    // 这样在使用时可以这么写,同样可以输出当前行号和文件名
    trace("printf message %s\n", "some reason");

    test("123");
    return 0;
}
