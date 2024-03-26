//
// Created by aecg on 2024/3/22.
//

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "cached_queue.h"

void CachedQueue_Init(CachedQueue *const me, char *fName,
                      int (*isFullFunc)(CachedQueue *const me),
                      int (*isEmptyFunc)(CachedQueue *const me),
                      int (*getSizeFunc)(CachedQueue *const me),
                      void (*insertFunc)(CachedQueue *const me, int k),
                      int (*removeFunc)(CachedQueue *const me),
                      void (*flushFunc)(CachedQueue *const me),
                      void (*loadFunc)(CachedQueue *const me)
) {
    me->queue = Queue_Create();

    me->numberElementsOnDisk = 0;
    strcpy(me->fileName, fName);

    me->outputQueue = Queue_Create();

    me->isFull = isFullFunc;
    me->isEmpty = isEmptyFunc;
    me->getSize = getSizeFunc;
    me->insert = insertFunc;
    me->remove = removeFunc;
    me->flush = flushFunc;
    me->load = loadFunc;
}

void CachedQueue_Cleanup(CachedQueue *const me) {
    Queue_Cleanup(me->queue);
}

/**
 * Operations
 */
int CachedQueue_isFull(CachedQueue *const me) {
    return me->queue->isFull(me->queue) && me->outputQueue->isFull(me->outputQueue);
}

int CachedQueue_isEmpty(CachedQueue *const me) {
    return me->queue->isEmpty(me->queue) && me->outputQueue->isEmpty(me->outputQueue) &&
           (me->numberElementsOnDisk == 0);
}

int CachedQueue_getSize(CachedQueue *const me) {
    return me->queue->getSize(me->queue) +
           me->outputQueue->getSize(me->outputQueue) +
           me->numberElementsOnDisk;
}

void CachedQueue_insert(CachedQueue *const me, int k) {
    if (me->queue->isFull(me->queue)) {
        // 队列满了写入文件
        me->flush(me);
    }
    me->queue->insert(me->queue, k);
}

int CachedQueue_remove(CachedQueue *const me) {
    if (!me->outputQueue->isEmpty(me->outputQueue)) {
        return me->outputQueue->remove(me->outputQueue);
    } else if (me->numberElementsOnDisk > 0) {
        me->load(me);
        return me->queue->remove(me->queue);
    } else {
        return me->queue->remove(me->queue);
    }
}

void CachedQueue_flush(CachedQueue *const me) {
    while (!me->queue->isEmpty(me->queue)) {
        me->queue->remove(me->queue);
        // write file
        ++me->numberElementsOnDisk;
    }
}

void CachedQueue_load(CachedQueue *const me) {
    while (!me->outputQueue->isFull(me->outputQueue) && (me->numberElementsOnDisk > 0)) {
        // read file
        --me->numberElementsOnDisk;
        me->outputQueue->insert(me->outputQueue, 123);
    }
}


CachedQueue *CachedQueue_Create(void) {
    CachedQueue *me = (CachedQueue *) malloc(sizeof(CachedQueue));
    char *fileName = "/Users/aecg/CLionProjects/LearnC/c_design_patterns/queuebuffer.dat";
    if (me != NULL) {
        CachedQueue_Init(me, fileName, CachedQueue_isFull, CachedQueue_isEmpty, CachedQueue_getSize, CachedQueue_insert,
                         CachedQueue_remove, CachedQueue_flush, CachedQueue_load);
    }
    return me;
}

void CachedQueue_Destroy(CachedQueue *const me) {
    if (me != NULL) {
        CachedQueue_Cleanup(me);
    }
    free(me);
}