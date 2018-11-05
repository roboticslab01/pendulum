#include "sensor.h"

void encoder(){
  counter++;
  //Serial.println(counter);
}

float myMap(long sensorRead, int res) {
  return (360.0 / float(res)) * float(sensorRead) - 180.0;
}

int cyclicMap(int currentPos, int zeroPos, int res) {
  int cyclicVal = currentPos % zeroPos;
  if (currentPos < zeroPos) {
    cyclicVal = cyclicVal + (res - zeroPos);
  }
  return cyclicVal;
}

int greyCodeData() {
  int greyCode = 0;
  int status = !digitalRead(encPin[9]);
  //Serial.print(status);
  greyCode =   status * pow(2, 9);
  status = !digitalRead(encPin[8]);
  //Serial.print(status);
  greyCode =   greyCode + status * pow(2, 8);
  status = !digitalRead(encPin[7]);
  //Serial.print(status);
  greyCode =   greyCode + status * pow(2, 7);
  status = !digitalRead(encPin[6]);
  //Serial.print(status);
  greyCode =   greyCode + status * pow(2, 6);
  status = !digitalRead(encPin[5]);
  //Serial.print(status);
  greyCode =   greyCode + status * pow(2, 5);
  status = !digitalRead(encPin[4]);
  //Serial.print(status);
  greyCode =   greyCode + status * pow(2, 4);
  status = !digitalRead(encPin[3]);
  //Serial.print(status);
  greyCode =   greyCode + status * pow(2, 3);
  status = !digitalRead(encPin[2]);
  //Serial.print(status);
  greyCode =   greyCode + status * pow(2, 2);
  status = !digitalRead(encPin[1]);
  //Serial.print(status);
  greyCode =   greyCode + status * pow(2, 1);
  status = !digitalRead(encPin[0]);
  //Serial.print(status);
  greyCode =   greyCode + status * pow(2, 0);
  //Serial.println( greyCode );
  //Serial.println();
  return greyCode;
}

int getEncData() {
  long num = greyCodeData();
  //Serial.print("Grey Code = "); Serial.println(greyCode);
  num = num ^ (num >> 16);
  num = num ^ (num >> 8);
  num = num ^ (num >> 4);
  num = num ^ (num >> 2);
  num = num ^ (num >> 1);
  //Serial.println(num);
  return int(num);
}


