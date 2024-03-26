//
// Created by aecg on 2024/3/22.
//

#ifndef LEARNC_QUEUE_H
#define LEARNC_QUEUE_H

#define QUEUE_SIZE 10

typedef struct Queue Queue;

struct Queue {
    int buffer[QUEUE_SIZE];
    int head;
    int size;
    int tail;
    int (*isFull)(Queue* const me);
    int (*isEmpty)(Queue* const me);
    int (*getSize)(Queue* const me);
    void (*insert)(Queue* const me, int k);
    int (*remove)(Queue* const me);
};

void Queue_Init(Queue* const me,
                int (*isFullFunc)(Queue* const me),
                int (*isEmptyFunc)(Queue* const me),
                int (*getSizeFunc)(Queue* const me),
                void (*insertFunc)(Queue* const me, int k),
                int (*removeFunc)(Queue* const me));

void Queue_Cleanup(Queue* const me);

/**
 * Operations
 */
int Queue_isFull(Queue* const me);
int Queue_isEmpty(Queue* const me);
int Queue_getSize(Queue* const me);
void Queue_insert(Queue* const me, int k);
int Queue_remove(Queue* const me);

Queue *Queue_Create(void);
void Queue_Destroy(Queue* const me);

#endif //LEARNC_QUEUE_H
