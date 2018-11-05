#ifndef ENCODER_H
#define ENCODER_H

//pin list
unsigned char encPin[] = {36, 38, 40, 42, 44, 46, 48, 50, 52, 53};
unsigned char incEncpin[] = {19, 18};
unsigned char limitpin[2] = {2, 3};

//incremental variables
int counter = 0;
float distance = 0;
//absolute variables
float degree=0;
int absdata = 0;
int lastdata = 0;
int cyclic_data = 0;
int encResolution = 1024;
int zero = 512;//679

//function list
void readincEncoder();
void readabsEncoder();
float myMap(long sensorRead, int res);
int cyclicMap(int currentPos, int zeroPos, int res);
int greyCodeData();
int getEncData();

#endif
