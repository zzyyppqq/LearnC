//
// Created by 张宜鹏 on 2023/2/17.
//

#include <iostream>
#include <fstream>

template<typename T>
void read(std::ifstream& ifs, T& data)
{
    ifs.read(reinterpret_cast<char*>(&data), sizeof(T));
}

int main()
{
    std::ifstream ifs("data", std::ios::in | std::ios::binary);

    uint64_t f1;
    int32_t  f2;
    double   f3;

    while(1)
    {
        read(ifs, f1);
        read(ifs, f2);
        read(ifs, f3);

        if (ifs.eof())
            break;

        std::cout << f1 << ' ' << f2 << ' ' << f3 << '\n';
    }
    return 0;
}