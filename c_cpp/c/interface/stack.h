//
// Created by 张宜鹏 on 2022/11/3.
//

#ifndef CPPSTUDY_STACK_H
#define CPPSTUDY_STACK_H

// 抽象数据类型
#define T Stack_T
typedef struct T *T;
extern T   Stack_new (void);
extern int  Stack_empty(T stk);
extern void Stack_push (T stk, void *x);
extern void *Stack_pop (T stk);
extern void Stack_free (T *stk);
#undef T

#endif //CPPSTUDY_STACK_H
