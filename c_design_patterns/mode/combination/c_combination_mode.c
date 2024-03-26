//
// Created by aecg on 2024/3/25.
//
#include "stdlib.h"
#include "stdio.h"
#include "assert.h"

typedef struct _Object {
    //struct _Object* ppObject[100];
    struct _Object** ppObject;
    int number;
    void (*operate)(struct _Object* pObject)
} Object;


void operate_of_parent(struct _Object* pObject) {
    int index;
    assert(NULL != pObject);
    assert(NULL != pObject->ppObject && 0 != pObject->number);

    for (int index = 0; index < pObject->number; ++index) {
        pObject->ppObject[index]->operate(pObject->ppObject[index]);
    }

}

void operate_of_child(struct _Object *pObject) {
    assert(NULL != pObject);
    printf("child node!\n");
}

void process(struct _Object* pObject){
    assert(NULL != pObject);
    pObject->operate(pObject);
}

int main() {
    struct _Object pObject;
    pObject.operate = operate_of_parent;
    pObject.number = 100;
//    pObject.ppObject =
    process(&pObject);
}
