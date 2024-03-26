//
// Created by 张宜鹏 on 2022/4/19.
//
#include <iostream>
using namespace std;

namespace first_space {
    void func() {
        cout << "Inside first_space" << endl;
    }
}

namespace second_space {
    void func() {
        cout << "Inside second_space" << endl;
    }
    namespace third_space {
        void func() {
            cout << "Inside third_space" << endl;
        }
    }
}

int main() {

    first_space::func();
    second_space::func();
    second_space::third_space::func();
}
