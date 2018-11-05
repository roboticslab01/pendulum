#include "sensor.h"
#include "motordriver.h"
#include "control.h"
#define tbPID   digitalRead(button[0]==HIGH)
#define tbLQR   digitalRead(button[1]==HIGH)

typedef struct{
  float kp;
  float ki;
  float kd;
}PID;

typedef struct{
  float k_omega;
  float k_theta;
  float k_thetaDot;
}LQR;

//PID and LQR variable definition

PID pid={30,0,250};//kp,ki,kd

PID pid1={0,0,0};//kp,ki,kd

LQR lqr={-0.03,-50,-70.7};//k_omegar, k_theta, k_thetaDot

//global variable
unsigned char encPin[] = {14, 15, 16, 17, 18, 19, 3, 4, 5, 6};
unsigned char button[2]={11,12};
int encResolution = 1023;
long lastmillis=0;

float smallAngle = 20.0;
int zero = 674;//679
float maxDrive = 900;
float minDrive = 100;
float degree;
float Kp, Ki, Kd;
byte pendDir = 2;

int i = 0;
float Wr = 0.;
float ppr = 4.;

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 10; i++) {
    pinMode(encPin[i], INPUT_PULLUP);
  }
  for(int i = 0; i<2; i++){
    pinMode(button[i], INPUT_PULLUP);  
  }
  pinMode(2,INPUT);
  digitalWrite(2,LOW);
  attachInterrupt(0,encoder,RISING);
  Serial.begin(9600);
  setupPWM16();
  motor_stop();
}

void loop() {
  // put your main code here, to run repeatedly:
start:
  while(1){
    sumErr = 0.0;
    counter = 0;
    if(!tbPID){
      while(!tbPID){}
      goto modePID;  
    }
    if(!tbPID){
      while(!tbLQR){}
      goto modeLQR;  
    }
    delay(150);
  }
modePID:
  while(1){
    int sensorRead = getEncData();
    sensorRead = cyclicMap(sensorRead, zero, encResolution);
    degree = myMap(sensorRead, encResolution);
    if ((abs(degree) >= 0) && (abs(degree) < smallAngle)) {
      Kp = pid.kp;
      Kd = pid.kd;
      Ki = pid.ki;
      //Serial.println("sudut kecil");
    }
    else {
      Kp = pid1.kp;
      Ki = pid1.ki;
      Kd = pid1.kd;
      //Serial.println("sudut besar");
    }
    int mtrControlSignal = int(computePID(degree));
    int absMtrCS = abs(mtrControlSignal);
    int pwmVal = map(absMtrCS, 0, maxDrive, minDrive, maxDrive);
    if (mtrControlSignal < 0) pendDir = 1;
    else if (mtrControlSignal > 0) pendDir = 0;
    else pendDir = 2;
    motorWheelDrive(pendDir, pwmVal);
    if(!tbPID){
      while(!tbPID){}
      break;
    } 
  }
  motor_stop();
  goto start;
modeLQR:
  while(1){
    int sensorRead = getEncData();
    sensorRead = cyclicMap(sensorRead, zero, encResolution);
    degree = myMap(sensorRead, encResolution);
    theta = degree;
    theta_dot = degree - last_theta;
    if(millis()-lastmillis>1000){
      lastmillis=millis();
      omega_r = abs(counter) / ppr * 2 * 3.14; //rad/s // rps
      counter=0;  
    }
    int mtrControlSignal;
    if ((abs(degree) >= 0) && (abs(degree) < smallAngle)) {
      mtrControlSignal = int(computeLQR(theta, theta_dot, omega_r));
    }
    else {
      mtrControlSignal = 0;
    }
    int absMtrCS = abs(mtrControlSignal);
    int pwmVal = map(absMtrCS, 0, maxDrive, minDrive, maxDrive);
    if (mtrControlSignal < 0)pendDir = 1;
    else if (mtrControlSignal > 0)pendDir = 0;
    else pendDir = 2; 
    motorWheelDrive(pendDir, pwmVal);
    if(!tbLQR){
      while(!tbLQR){}
      break;
    }
  }
  motor_stop();
  goto start;
}
