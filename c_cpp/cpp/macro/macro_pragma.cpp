//
// Created by 张宜鹏 on 2023/2/6.
//


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

int main() {

    return 1;
}