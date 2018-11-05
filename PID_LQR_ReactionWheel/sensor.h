#ifndef SENSOR_H
#define SENSOR_H

int counter=0;

void encoder();
float myMap(long sensorRead, int res);
int cyclicMap(int currentPos, int zeroPos, int res);
int greyCodeData();
int getEncData();

#endif
