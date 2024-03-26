//
// Created by aecg on 2024/3/22.
//

#ifndef LEARNC_CACHEDQUEUE_H
#define LEARNC_CACHEDQUEUE_H

#include "queue.h"

typedef struct CachedQueue CachedQueue;

struct CachedQueue {
    Queue *queue;
    char fileName[80];
    int numberElementsOnDisk;

    Queue* outputQueue;

    int (*isFull)(CachedQueue* const me);
    int (*isEmpty)(CachedQueue* const me);
    int (*getSize)(CachedQueue* const me);
    void (*insert)(CachedQueue* const me, int k);
    int (*remove)(CachedQueue* const me);

    void (*flush)(CachedQueue* const me);
    void (*load)(CachedQueue* const me);
};


void CachedQueue_Init(CachedQueue* const me, char *fName,
                int (*isFullFunc)(CachedQueue* const me),
                int (*isEmptyFunc)(CachedQueue* const me),
                int (*getSizeFunc)(CachedQueue* const me),
                void (*insertFunc)(CachedQueue* const me, int k),
                int (*removeFunc)(CachedQueue* const me),
                void (*flushFunc)(CachedQueue* const me),
                void (*loadFunc)(CachedQueue* const me)
);

void CachedQueue_Cleanup(CachedQueue* const me);

/**
 * Operations
 */
int CachedQueue_isFull(CachedQueue* const me);
int CachedQueue_isEmpty(CachedQueue* const me);
int CachedQueue_getSize(CachedQueue* const me);
void CachedQueue_insert(CachedQueue* const me, int k);
int CachedQueue_remove(CachedQueue* const me);
void CachedQueue_flush(CachedQueue* const me);
void CachedQueue_load(CachedQueue* const me);


CachedQueue *CachedQueue_Create(void);
void CachedQueue_Destroy(CachedQueue* const me);

#endif //LEARNC_CACHEDQUEUE_H
