//
// Created by 张宜鹏 on 2023/2/2.
//

/// [C++中指向指针的指针的作用_Lavi_qq_2910138025的博客-CSDN博客](https://blog.csdn.net/liuweiyuxiang/article/details/84769438 )

/// 在子函数中修改主函数传过来的指针的指向

#include<stdio.h>

int find(char *s, char src, char **rt)//从s中查询出src字符所在的位置并在rt中返回。
{
    int i = 0;
    while (*(s + i)) {
        if (*(s + i) == src)//只会出现一次满足条件，此时将此地址给*rt，即p
        {
            *rt = s + i;//这里修改了p的指向
        }
        i++;
    }
    return 0;
}


int main(void) {
    char a[10] = "zhuyujia";
    char *p = NULL;
    find(a, 'y', &p);//改变p的指向，在子函数中实现
    printf("%s", p);
    getchar();
    getchar();

    // 打印指针的时候，会把指针所指向的内容以及至字符串末位的内容都打印出来
    char a2[10] = "abcdefgff";
    char* p2 = &a2[6];
    printf("%s", p2);//会打印gff

    return 0;
}