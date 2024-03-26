
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <signal.h>
#include <execinfo.h>

// 0: GENERATE COREDUMP FILE
// 1: PRINT STACK BY SELF
int g_iTestFlag = 1;
#define ADDR_MAX_NUM 100

void CallbackSignal (int iSignalNo) {
    printf ("CALLBACK: SIGNAL:\n", iSignalNo);
    void *pBuf[ADDR_MAX_NUM] = {0};
    int iAddrNum = backtrace(pBuf, ADDR_MAX_NUM);
    printf("BACKTRACE: NUMBER OF ADDRESSES IS:%d\n\n", iAddrNum);
    char ** strSymbols = backtrace_symbols(pBuf, iAddrNum);
    if (strSymbols == NULL) {
        printf("BACKTRACE: CANNOT GET BACKTRACE SYMBOLS\n");
        return;
    }
    int ii = 0;
    for (ii = 0; ii < iAddrNum; ii++) {
        printf("%03d %s\n", iAddrNum-ii, strSymbols[ii]);
    }
    printf("\n");
    free(strSymbols);
    strSymbols = NULL;
    exit(1); // QUIT PROCESS. IF NOT, MAYBE ENDLESS LOOP.
}

void FuncBadBoy() {
    void* pBadThing = malloc(1024*1024*256);
    free (pBadThing);
    free (pBadThing);
}

void FuncBadFather() {
    FuncBadBoy();
}

int main(int argc, char **argv){
    if (g_iTestFlag) {
        signal(SIGSEGV, CallbackSignal);
    }
    FuncBadFather();
    return 0;
}