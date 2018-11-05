#include <EEPROM.h>
#include "encoder.h"
#include "driver.h"
#include "lqrcontrol.h"
#define   savedata  digitalRead(4)==HIGH  

unsigned char penDir = 1;
float x=0, last_x=0, x_dot=0;
float theta=0, last_theta=0, theta_dot=0;
float smallAngle = 20.0;
float maxDrive = 1023;
float minDrive = 200;
int ezero=0;

LQRvar cons={-103.2,-103.5,-274.9,-150.7};
PIDvar cons1={-200,-10,-250};

void setup() {
  // put your setup code here, to run once:
  for(byte i=0;i<10;i++){
    pinMode(encPin[i],INPUT_PULLUP);  //absolute encoder pin
  }
  for(byte i=0;i<2;i++)
  {
    pinMode(incEncpin[i],INPUT_PULLUP); //incremental encoder pin
    pinMode(limitpin[i],INPUT_PULLUP);  //limit switch pin
    //pinMode(motorEn[i],OUTPUT);
  }
  pinMode(4,INPUT_PULLUP);
  attachInterrupt(0,limit_pressed,FALLING);
  attachInterrupt(1,limit_pressed,FALLING);
  pinMode(2,INPUT_PULLUP);
  attachInterrupt(4,encoders,RISING);
  setupPWM16();
  Serial.begin(9600);
  init_pos();
  //zero = EEPROM.read(ezero);
  Serial.println(zero);
}

//input LQR constanta here cons = { k1, k2, k3, k3}

void loop() {
  absdata = getEncData(); //encoder true data 
  cyclic_data = cyclicMap(absdata, zero, encResolution); //encoder map data 
  degree = myMap(cyclic_data, encResolution); //encoder degree data //theta
  distance = readPosition(counter); //x
  x = distance;
  //if(x!=last_x){
  //  Serial.print(x);Serial.println(" cm");
  //  last_x = x;
  //}
  theta = degree;
  x_dot = x - last_x;
  theta_dot = theta - last_theta;
  int LQRoutput;
  if ((abs(degree) >= 0) && (abs(degree) < smallAngle))
  {
    //LQRoutput = computeLQR1(x, theta, x_dot, theta_dot);
    LQRoutput = computePID(theta);
  }
  else LQRoutput = 0;
  int absLQRoutput = abs(LQRoutput);
  int pwmval = map(absLQRoutput,0,maxDrive,minDrive, maxDrive);
  Serial.println(pwmval);
  if(LQRoutput < 0)penDir=0;
  else if(LQRoutput> 0)penDir=1;
  else penDir=2;
  motorDrive(penDir,pwmval);
  last_x = x;
  last_theta = theta;
  if(!savedata){
    while(!savedata){}
    zero = absdata;
    counter = 0;
    Serial.print("Zero Position Updated : ");
    Serial.println(zero);
    EEPROMWritelong(ezero,zero);
  }
}

void limit_pressed(){
  //Serial.println(counter);
  if(penDir==1){
    while(digitalRead(limitpin[0])==LOW){motor_stop();}}//right limit
  else if(penDir==0){
    while(digitalRead(limitpin[1])==LOW){motor_stop();}//left limit
  }
}

void EEPROMWritelong(int address, long value)
{
      //Decomposition from a long to 4 bytes by using bitshift.
      //One = Most significant -> Four = Least significant byte
      byte four = (value & 0xFF);
      byte three = ((value >> 8) & 0xFF);
      byte two = ((value >> 16) & 0xFF);
      byte one = ((value >> 24) & 0xFF);

      //Write the 4 bytes into the eeprom memory.
      EEPROM.write(address, four);
      EEPROM.write(address + 1, three);
      EEPROM.write(address + 2, two);
      EEPROM.write(address + 3, one);
}

long EEPROMReadlong(long address)
{
      //Read the 4 bytes from the eeprom memory.
      long four = EEPROM.read(address);
      long three = EEPROM.read(address + 1);
      long two = EEPROM.read(address + 2);
      long one = EEPROM.read(address + 3);

      //Return the recomposed long by using bitshift.
      return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}
