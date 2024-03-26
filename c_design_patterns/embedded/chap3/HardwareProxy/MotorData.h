//
// Created by aecg on 2024/3/22.
//

#ifndef LEARNC_MOTORDATA_H
#define LEARNC_MOTORDATA_H

#include "HWProxyExample.h"
typedef struct MotorData MotorData;
struct MotorData {
    unsigned char on_off;
    DirectionType direction;
    unsigned int speed;
    unsigned char errorStatus;
    unsigned char noPowerError;
    unsigned char noTorqueError;
    unsigned char BITError;
    unsigned char overTemperatureError;
    unsigned char reservedError1;
    unsigned char reservedError2;
    unsigned char unknownError;
};

#endif //LEARNC_MOTORDATA_H
