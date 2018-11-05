#ifndef LQRCONTROL_H
#define LQRCONTROL_H

typedef struct{
    float k1;
    float k2;
    float k3;
    float k4;
}LQRvar;

typedef struct{
  float kp;
  float ki;
  float kd;  
}PIDvar;

float err, lastErr, sumErr;

#endif
