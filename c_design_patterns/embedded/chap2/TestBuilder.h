//
// Created by aecg on 2024/3/22.
//

#ifndef LEARNC_TESTBUILDER_H
#define LEARNC_TESTBUILDER_H

#include "stdio.h"
#include "ECGPkg.h"
#include "ArrythmiaDetector.h"
#include "ECG_Module.h"
#include "HistogramDisplay.h"
#include "QRSDelector.h"
#include "TMDQueue.h"
#include "WaveformDisplay.h"


typedef struct TestBuilder TestBuilder;
struct TestBuilder  {
    struct ArrythmiaDetector itsArrythmiaDetector;
    struct ECG_Module itsECG_Module;
    struct HistogramDisplay itsHistogramDisplay;
    struct QRSDetector itsQRSDetector;
    struct TMDQueue itsTMDQueue;
    struct WaveformDisplay itsWaveformDisplay;
};

void TestBuilder_Init(TestBuilder* const me);
void TestBuilder_Cleanup(TestBuilder* const me);

struct ArrythmiaDetector * TestBuilder_getArrythmiaDetector(const TestBuilder* const me);
struct ECG_Module * TestBuilder_getECG_Module(const TestBuilder* const me);
struct HistogramDisplay * TestBuilder_getHistogramDisplay(const TestBuilder* const me);
struct QRSDetector * TestBuilder_getQRSDetector(const TestBuilder* const me);
struct TMDQueue * TestBuilder_getTMDQueue(const TestBuilder* const me);
struct WaveformDisplay * TestBuilder_getWaveformDisplay(const TestBuilder* const me);

TestBuilder *TestBuilder_Create(void);
void TestBuilder_Destroy(TestBuilder* const me);


#endif //LEARNC_TESTBUILDER_H
