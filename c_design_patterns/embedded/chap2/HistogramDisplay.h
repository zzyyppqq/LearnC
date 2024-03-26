//
// Created by aecg on 2024/3/22.
//

#ifndef LEARNC_HISTOGRAMDISPLAY_H
#define LEARNC_HISTOGRAMDISPLAY_H

#include "stdio.h"
#include "ECGPkg.h"

struct TMDQueue;

typedef struct HistogramDisplay HistogramDisplay;

struct HistogramDisplay {
    int index;
    struct TMDQueue *itsTMDQueue;
};


void HistogramDisplay_Init(HistogramDisplay *const me);

void HistogramDisplay_Cleanup(HistogramDisplay *const me);

void HistogramDisplay_getValue(HistogramDisplay *const me);

void HistogramDisplay_updateHistogram(HistogramDisplay *const me);

struct TMDQueue *HistogramDisplay_getItsTMDQueue(const HistogramDisplay *const me);

void HistogramDisplay_setItsTMDQueue(HistogramDisplay *const me, struct TMDQueue *p_TMDQueue);

HistogramDisplay* HistogramDisplay_Create(void);
void HistogramDisplay_Destroy(HistogramDisplay* const me);

#endif //LEARNC_HISTOGRAMDISPLAY_H
