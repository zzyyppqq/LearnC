//
// Created by 张宜鹏 on 2023/2/17.
//

#include <iostream>

#include <string>
#include <vector>
#include <string.h>

using namespace std;

int main() {
    int arr[5];
    arr[1] = 1;
    arr[2] = 2;
    arr[3] = 3;
    // 模拟数据，int数组arr 实际长度 为 3

    int len = end(arr)-begin(arr);
    int len2 =  sizeof(arr) / sizeof(arr[0]);
    cout <<"-----len-------"<< len << endl;
    cout <<"-----len2-------"<< len2 << endl;

    char str[5];
    str[0] = 'a';
    str[1] = 'b';
    str[2] = 'c';
    // 模拟数据，int数组arr 实际长度 为 3

    int str_len = end(arr)-begin(arr);
    int str_len2 =  sizeof(arr) / sizeof(arr[0]);
    cout <<"-----str len-------"<< str_len << endl;
    cout <<"-----str len2-------"<< str_len2 << endl;
    cout <<"-----str len3-------"<< std::strlen(str) << endl;
    cout <<"-----str len4-------"<< strlen(str) << endl;

    // 以上求长度方法打印的 int数组arr 为 5

    // 求int 数组arr 的实际长度
    int size = 0;
    for(int i = 0; i < 5;i++) {
        if(arr[i]) {
            cout <<"-----arr[i]-------"<< arr[i] << endl;
            size ++;
        }
    }
    cout <<"-----total size-------"<< size << endl; // 3


    //---------------------------------------------------
    // 求 vector 数组data长度
    vector<int> data = {1, 2, 3, 4};

    int datalen = end(data)-begin(data);
    int datalen2 =  data.size();
    cout <<"-----datalen-------"<< datalen << endl;
    cout <<"-----datalen2-------"<< datalen2 << endl;

    return 0;
}