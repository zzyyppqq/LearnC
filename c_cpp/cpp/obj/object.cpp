//
// Created by 张宜鹏 on 2022/4/19.
//
#include <iostream>

using namespace std;

class Users {

public:

    int vx;

    Users(){
        cout << "data" << endl;
    }

    Users(int x) : vx(x) {}

    void msg() {
        cout << "msg" << endl;
    }

};


typedef struct col {
    int cid;
    float cscore;
    col(int id, float score) : cid{id}, cscore{score} {}

} collection;


int main() {
// create class data instances;
    Users a = Users();

    Users d = Users(3);

    Users *cpt = &d;

    d.msg();

    cpt->msg();

    // create struct col object

    collection c{1, 145.3};

    cout << c.cid << endl;

    cout << c.cscore << endl;


    collection *spt = &c;

    cout << spt->cid << endl;

    cout << spt->cscore << endl;

    return 0;
}