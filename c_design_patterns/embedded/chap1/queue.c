//
// Created by aecg on 2024/3/22.
//

#include "stdio.h"
#include "stdlib.h"
#include "queue.h"

void Queue_Init(Queue *const me,
                int (*isFullFunc)(Queue *const me),
                int (*isEmptyFunc)(Queue *const me),
                int (*getSizeFunc)(Queue *const me),
                void (*insertFunc)(Queue *const me, int k),
                int (*removeFunc)(Queue *const me)) {

    me->head = 0;
    me->size = 0;
    me->tail = 0;

    me->isFull = isFullFunc;
    me->isEmpty = isEmptyFunc;
    me->getSize = getSizeFunc;
    me->insert = insertFunc;
    me->remove = removeFunc;
}

void Queue_Cleanup(Queue *const me) {

}

int Queue_isFull(Queue *const me) {
    return (me->head + 1) % QUEUE_SIZE == me->tail;
}

int Queue_isEmpty(Queue *const me) {
    return me->head == me->tail;
}

int Queue_getSize(Queue *const me) {
    return me->size;
}

void Queue_insert(Queue *const me, int k) {
    if (!me->isFull(me)) {
        me->buffer[me->head] = k;
        me->head = (me->head + 1) % QUEUE_SIZE;
        ++me->size;
    }
}

int Queue_remove(Queue *const me) {
    int value = -9999;
    if (!me->isEmpty(me)) {
        value = me->buffer[me->tail];
        me->tail = (me->tail + 1) % QUEUE_SIZE;
        --me->size;
    }
    return value;
}

Queue *Queue_Create(void) {
    Queue *me = (Queue *) malloc(sizeof(Queue));
    if (me != NULL) {
        Queue_Init(me, Queue_isFull, Queue_isEmpty, Queue_getSize, Queue_insert, Queue_remove);
    }
    return me;
}

void Queue_Destroy(Queue *const me) {
    if (me != NULL) {
        Queue_Cleanup(me);
    }
    free(me);
}

int main() {
    int j, k, h, t;
    Queue * myQ;
    myQ = Queue_Create();
    k = 1000;

    for (j = 0; j < QUEUE_SIZE; j++) {
        h = myQ->head;
        myQ->insert(myQ, k);
        printf("inserting %d at position %d, size = %d\n", k--, h, myQ->getSize(myQ));
    }

    return 0;
}

