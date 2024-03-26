//
// Created by 张宜鹏 on 2023/2/2.
//

/// 用指针的指针取二维数组的元素

/*
#include<stdio.h
//错误的做法
int change(char **p)
{
	int i, j;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; *(*(p + i) + j) != '\0'; j++)
		{
			printf("%c", *(*(p + i) + j));
		}
		printf("\n");
	}
	return 0;
}
//若希望赋值，则不能使用指针的指针，要使用数组进行运算。
int change(char p[][10])
{
   int i, j;
   for (i = 0; i < 5; i++)
   {
     for (j = 0; p[i][j] != '\0'; j++)
     {
        p[i][j] = 'c';
        printf("%c", p[i][j]);
     }
     printf("\n");
   }
   return 0;
}
int main(void)
{
	char a[5][10] = { "hello", "zhuyu", "jiajia", "linux","Ubuntu" };
	change(a);
	return 0;
}
*/


#include<stdio.h>
int change(char **p)
{
    int i, j;
    for (i = 0; i < 5; i++)
    {
        for (j = 0; *(*(p + i) + j) != '\0'; j++)//利用指针的指针取二维数组的元素
        {
            *(*(p + i) + j) = 'c';
            printf("%c", *(*(p + i) + j));
        }
        printf("\n");
    }
    return 0;
}

int main(void)
{
    char a[5][10] = { "hello", "zhuyu", "jiajia", "linux","Ubuntu" };
    char *b[5] = { a[0],a[1],a[2],a[3],a[4] };//这样做读取和写入操作都是可以的。
    change(b);
    return 0;
}
