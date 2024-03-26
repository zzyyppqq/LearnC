//
// Created by 张宜鹏 on 2023/2/1.
//

#include <iostream>
#include <shared_mutex>
#include "my_version.h"

int main() {

    if (__cplusplus == 201703L) std::cout << "C++17\n";
    else if (__cplusplus == 201402L) std::cout << "C++14\n";
    else if (__cplusplus == 201103L) std::cout << "C++11\n";
    else if (__cplusplus == 199711L) std::cout << "C++98\n";
    else std::cout << "pre-standard C++\n";
    std::cout << "__cplusplus: " << __cplusplus << std::endl;

    std::recursive_mutex m0;
    std::mutex m;
    std::recursive_mutex m2;

    std::shared_mutex m3;
    std::shared_timed_mutex m4;


    return 0;
}