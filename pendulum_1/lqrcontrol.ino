#include "lqrcontrol.h"

int computeLQR(float ex, float th, float ex_dot, float th_dot){
  float val = constrain(cons.k1 * ex + cons.k2 * th + cons.k3 * ex_dot + cons.k4 * th_dot, -maxDrive, maxDrive);
  return val;
}

int computeLQR1(float ex, float th, float ex_dot, float th_dot){
  err = th;
  float dErr = th_dot;
  float val = constrain(cons.k1 * ex + cons1.kp * err + cons.k3 * ex_dot + cons1.kd * th_dot, -maxDrive, maxDrive);
  return val;
}

int computePID(float pendPos){
  err = pendPos;
  float dErr = err - lastErr;
  float P = cons1.kp * err;
  float D = cons1.kd * dErr;
  float I = cons1.ki * sumErr;
  float PID = constrain(P + I + D, -maxDrive, maxDrive);
  sumErr += err;
  lastErr = err;
  return PID;
}
