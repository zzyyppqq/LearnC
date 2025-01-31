//
// Created by aecg on 2024/3/22.
//

#ifndef LEARNC_TMDQUEUE_H
#define LEARNC_TMDQUEUE_H

#include "stdio.h"
#include "ECGPkg.h"
#include "TimeMarkedData.h"

typedef struct TMDQueue TMDQueue;

struct TMDQueue {
    int head;
    int size;
    TimeMarkedData buffer[QUEUE_SIZE];
};

void TMDQueue_Init(TMDQueue* const me);
void TMDQueue_Cleanup(TMDQueue* const me);

int TMDQueue_getNextIndex(TMDQueue* const me, int index);

void TMDQueue_insert(TMDQueue* const me, const struct TimeMarkedData tmd);

boolean TMDQueue_isEmpty(TMDQueue* const me);

struct TimeMarkedData TMDQueue_remove(TMDQueue* const me, int index);

int TMDQueue_getBuffer(const TMDQueue* const me);

TMDQueue* TMDQueue_Create(void);

void TMDQueue_Destroy(TMDQueue* const me);

#endif //LEARNC_TMDQUEUE_H
