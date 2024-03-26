#include "MotorProxy.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int *ptr = NULL;
    *ptr = 0;

    /* code */
    MotorProxy * motor = MotorProxy_Create();
    // config rotaryArmLength and motor address
    unsigned int rotaryArmLength = 10;
    unsigned int location = 0x7ffc936a;
    unsigned int motorData = 100;

    DirectionType direction;
    unsigned int speed;

    MotorProxy_configure(motor, rotaryArmLength, &location);
    printf("MotorProxy_configure: %d, %d, %d\r\n", motor->motorAddr, motor->rotaryArmLength, *motor->motorAddr);
    MotorProxy_initialize(motor);
    printf("MotorProxy_initialize: %d, %d, %d\r\n", motor->motorAddr, motor->rotaryArmLength, *motor->motorAddr);
    MotorProxy_enable(motor);

    direction = FORWARD;
    speed = 10;
    MotorProxy_writeMotorSpeed(motor, &direction, speed);
    printf("MotorProxy_writeMotorSpeed: %d, %d, %d\r\n", motor->motorAddr, motor->rotaryArmLength, *motor->motorAddr);
 
    DirectionType getdirection = MotorProxy_accessMotorDirection(motor);
    unsigned int getspeed = MotorProxy_accessMotorSpeed(motor);
    unsigned int getstate = MotorProxy_accessMotorState(motor);
    printf("Motor current direction:%d, speed:%d, state:%d\n", getdirection, getspeed, getstate);

    direction = REVERSE;
    speed = 20;
    MotorProxy_writeMotorSpeed(motor, &direction, speed);
    getdirection = MotorProxy_accessMotorDirection(motor);
    getspeed = MotorProxy_accessMotorSpeed(motor);
    getstate = MotorProxy_accessMotorState(motor);
    printf("Motor current direction:%d, speed:%d, state:%d\n", getdirection, getspeed, getstate);

    MotorProxy_disable(motor);
    getdirection = MotorProxy_accessMotorDirection(motor);
    getspeed = MotorProxy_accessMotorSpeed(motor);
    getstate = MotorProxy_accessMotorState(motor);
    printf("Motor current direction:%d, speed:%d, state:%d\n", getdirection, getspeed, getstate);

    MotorProxy_Destroy(motor);
    return 0;
}