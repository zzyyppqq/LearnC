//
// Created by aecg on 2024/3/22.
//

#include "stdlib.h"
#include "stdio.h"

#define TURN_OFF (0x00)
#define INITIALIZE (0x61)
#define RUN (0x69) // 0110 1001
#define CHECK_ERROR (0x02)
#define DEVICE_ADDRESS (0x01FFAFD0)
//#define DEVICE_ADDRESS (0x7ff7b24e32a8)

void emergencyShutDown(void) {
    printf("OMG We're all gonna die!\n");
}

int main() {
    unsigned char *pDevice;
    //pDevice = (unsigned char *) DEVICE_ADDRESS;

    pDevice = malloc(1);
    printf("Device bits %p\n", &pDevice);
    *pDevice = 0xFF;
    printf("Device bits %X\n", *pDevice);
    *pDevice = *pDevice & INITIALIZE;
    printf("Device bits %X\n", *pDevice);
    if (*pDevice & CHECK_ERROR) {
        emergencyShutDown();
        abort();
    } else {
        *pDevice = *pDevice & RUN;
        printf("Device bits %X\n", *pDevice);
    }

}