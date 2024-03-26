//
// Created by aecg on 2024/3/22.
//

#include <stdlib.h>
#include <stdio.h>
#include "sensor.h"

void Sensor_Init(Sensor *const me) {

}

void Sensor_Cleanup(Sensor *const me) {

}

int Sensor_getFilterFrequency(const Sensor *const me) {
    return me->filterFrequency;
}

void Sensor_setFilterFrequency(Sensor *const me, int p_filterFrequency) {
    me->filterFrequency = p_filterFrequency;
}

int Sensor_getUpdateFrequency(const Sensor *const me) {
    return me->updateFrequency;
}

void Sensor_setUpdateFrequency(Sensor *const me, int p_updateFrequency) {
    me->updateFrequency = p_updateFrequency;
}

int Sensor_getValue(const Sensor *const me) {
    return me->value;
}

Sensor *Sensor_Create(void) {
    Sensor *me = (Sensor *) malloc(sizeof(Sensor));
    if (me != NULL) {
        Sensor_Init(me);
    }
    return me;
}

void Sensor_Destroy(Sensor *const me) {
    if (me != NULL) {
        Sensor_Cleanup(me);
    }
    free(me);
}


int main() {
    Sensor *p_Sensor0, *p_Sensor1;
    p_Sensor0 = Sensor_Create();
    p_Sensor1 = Sensor_Create();

    p_Sensor0->value = 99;
    p_Sensor1->value = -1;

    printf("p_Sensor0 value: %d\n", Sensor_getValue(p_Sensor0));
    printf("p_Sensor1 value: %d\n", Sensor_getValue(p_Sensor1));

    Sensor_Destroy(p_Sensor0);
    Sensor_Destroy(p_Sensor1);

    return 0;
}


