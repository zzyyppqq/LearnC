//
// Created by aecg on 2024/3/22.
//

#ifndef LEARNC_ECG_MODULE_H
#define LEARNC_ECG_MODULE_H

#include "stdio.h"
#include "ECGPkg.h"

struct TMDQueue;

typedef struct ECG_Module ECG_Module;
struct ECG_Module {
    int dataNum;
    int lead1;
    int lead2;
    struct TMDQueue *itsTMDQueue;
};

void ECG_Module_Init(ECG_Module *const me);

void ECG_Module_Cleanup(ECG_Module *const me);

void ECG_Module_acquireValue(ECG_Module *const me);

void ECG_Module_setLeadPair(ECG_Module *const me, int l1, int l2);

struct TMDQueue *ECG_Module_getItsTMDQueue(const ECG_Module *const me);

void ECG_Module_setItsTMDQueue(ECG_Module *const me, struct TMDQueue *p_TMDQueue);

ECG_Module *ECG_Module_Create(void);

void ECG_Module_Destroy(ECG_Module *const me);


#endif //LEARNC_ECG_MODULE_H
