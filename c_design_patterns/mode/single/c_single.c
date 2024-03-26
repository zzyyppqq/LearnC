#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

typedef struct _DATA {
    void *pData;
} DATA;

void *get_instance() {
    static DATA *pData = NULL;
    if (NULL != pData) {
        return pData;
    }

    pData = (DATA *) malloc(sizeof(DATA));
    assert(NULL != pData);
    return (void *) pData;
}


int main() {
    DATA *pData1 = get_instance();
    DATA *pData2 = get_instance();
    printf("pData1: %p, pData2: %p", pData1, pData2);
    return 0;
}
