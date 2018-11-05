#include "encoder.h"

void encoders(){
  if(digitalRead(incEncpin[1])==HIGH)counter--;
  else counter++;
  //Serial.println(counter);  
}

float readPosition(float input){
  return (input*0.20952381);
}

void readabsEncoder(){
  /*if(absdata!=lastdata){
    Serial.print("\t");
    Serial.print(absdata);
    Serial.print("\t");
    Serial.print(cyclic_data);
    Serial.print("\t");
    Serial.println(degree);  
    lastdata = absdata;
  }*/
}

void init_pos(){
  absdata = getEncData(); //encoder true data 
  cyclic_data = cyclicMap(absdata, zero, encResolution); //encoder map data 
  degree = myMap(cyclic_data, encResolution); //encoder degree data //theta
  Serial.print("position = ");Serial.println(absdata);
  Serial.print("\tzero = ");Serial.println(zero);
}

float myMap(long sensorRead, int res) {
  return (float(sensorRead) / float(res)) * 360 - 180.0;
}

int cyclicMap(int currentPos, int zeroPos, int res) {
  int cyclicVal = 0 ;
  if (currentPos < zeroPos) {
    cyclicVal = (currentPos % zeroPos)+ (res - zeroPos);
  }
  else cyclicVal = currentPos - zeroPos;
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
