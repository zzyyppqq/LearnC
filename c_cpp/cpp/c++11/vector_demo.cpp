//
// Created by zhangyipeng on 2023/8/1.
//

#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main() {

    vector<int> ivec;
    vector<int> ivec2(ivec);
    vector<int> ivec3 = ivec;
    vector<string> articles = {"a", "an", "the"};
    vector<string> articles2{"a", "an", "the"};

    vector<int> ivec4(10, -1);
    vector<string> svec4(10, "hi!");
    vector<string> svec5{10, "hi!"};

    vector<int> v;
    for (int i = 1; i < 10; ++i) {
        v.push_back(i);
    }
    int *pos = v.data();
    std::cout << *pos << std::endl;

    for (int i = 0; i < v.size(); ++i) {
        std::cout << *pos++ << " ";
    }
    std::cout << std::endl;

    for (auto &i: v) {
        i *= i;
    }
    for (auto i: v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    auto mid = v.begin() + v.size() / 2;


    return 0;
}

