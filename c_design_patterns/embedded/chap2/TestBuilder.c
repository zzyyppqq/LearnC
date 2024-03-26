//
// Created by aecg on 2024/3/22.
//

#include "TestBuilder.h"
#include "stdlib.h"

static void initRelations(TestBuilder *const me);

static void cleanUpRelations(TestBuilder *const me);

void TestBuilder_Init(TestBuilder *const me) {
    initRelations(me);
}

void TestBuilder_Cleanup(TestBuilder *const me) {
    cleanUpRelations(me);
}

struct ArrythmiaDetector *TestBuilder_getArrythmiaDetector(const TestBuilder *const me) {
    // 去地址，强转指针
    return (struct ArrythmiaDetector *) &(me->itsArrythmiaDetector);
}

struct ECG_Module *TestBuilder_getECG_Module(const TestBuilder *const me) {
    return (struct ECG_Module *)&(me->itsECG_Module);
}

struct HistogramDisplay *TestBuilder_getHistogramDisplay(const TestBuilder *const me) {
    return (struct HistogramDisplay *)&(me->itsHistogramDisplay);
}

struct QRSDetector *TestBuilder_getQRSDetector(const TestBuilder *const me) {
    return (struct QRSDetector *)&(me->itsQRSDetector);
}

struct TMDQueue *TestBuilder_getTMDQueue(const TestBuilder *const me) {
    return (struct TMDQueue *)&(me->itsTMDQueue);
}

struct WaveformDisplay *TestBuilder_getWaveformDisplay(const TestBuilder *const me) {
    return (struct WaveformDisplay *)&(me->itsWaveformDisplay);
}

TestBuilder *TestBuilder_Create(void) {
    TestBuilder * me = (TestBuilder*) malloc(sizeof (TestBuilder));
    if (me != NULL) {
        TestBuilder_Init(me);
    }
    return me;
}

void TestBuilder_Destroy(TestBuilder *const me) {
    if (me != NULL) {
        TestBuilder_Cleanup(me);
    }
    free(me);
}


static void initRelations(TestBuilder *const me) {
    ECG_Module_Init(&(me->itsECG_Module));
    TMDQueue_Init(&(me->itsTMDQueue));
    HistogramDisplay_Init(&(me->itsTMDQueue));

    ECG_Module_setItsTMDQueue(&(me->itsECG_Module), &(me->itsTMDQueue));
    HistogramDisplay_setItsTMDQueue(&(me->itsHistogramDisplay), &(me->itsTMDQueue));

}

static void cleanUpRelations(TestBuilder *const me) {
    ECG_Module_Cleanup(&(me->itsECG_Module));
}


int main() {
    int status = 0;

    TestBuilder *p_TestBuilder;
    p_TestBuilder = TestBuilder_Create();
    ECG_Module_acquireValue(&(p_TestBuilder->itsECG_Module));
    ECG_Module_acquireValue(&(p_TestBuilder->itsECG_Module));
    ECG_Module_acquireValue(&(p_TestBuilder->itsECG_Module));
    ECG_Module_acquireValue(&(p_TestBuilder->itsECG_Module));
    ECG_Module_acquireValue(&(p_TestBuilder->itsECG_Module));

    HistogramDisplay_getValue(&(p_TestBuilder->itsHistogramDisplay));
    HistogramDisplay_getValue(&(p_TestBuilder->itsHistogramDisplay));
    HistogramDisplay_getValue(&(p_TestBuilder->itsHistogramDisplay));
    HistogramDisplay_getValue(&(p_TestBuilder->itsHistogramDisplay));
    HistogramDisplay_getValue(&(p_TestBuilder->itsHistogramDisplay));

    printf("Done\n");
    TestBuilder_Destroy(p_TestBuilder);
    return 0;
}
