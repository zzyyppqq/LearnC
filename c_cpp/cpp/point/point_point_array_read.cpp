//
// Created by 张宜鹏 on 2023/2/2.
//

/// 用指针的指针指向指针数组

#include<stdio.h>
int change(char **p)
{
    int i, j;
    for (i = 0; i < 5; i++)
    {
        for (j = 0; *(*(p + i) + j) != '\0'; j++)//利用指针的指针取二维数组的元素
        {
            // 只能读取，不能写入
            *(*(p + i) + j) = 'c';
            printf("%c", *(*(p + i) + j));
        }
        printf("\n");
    }
    return 0;
}

int main(void)
{
    char *a[5] = { "hello", "zhuyu", "jiajia", "linux","Ubuntu" };//如果想使用 需使用指针数组即*a[5] 声明一个有五个字符串指针的数组。
    //但是由于每个元素都是指针字符串，所以只能够读取，而不能够写入。
    change(a);
    return 0;
}
