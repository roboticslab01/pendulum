#include "control.h"

int computePID(float pendPos) {
  err = pendPos - ref;
  dErr = err - lastErr;
  float P = Kp * err;
  float D = Kd * dErr;
  float I = Ki * sumErr;
  float PID = constrain(P + I + D, -maxDrive, maxDrive);
  sumErr += err;
  lastErr = err;
  return PID;
}

int computeLQR(float th, float th_dot, float omg_r){
  float val = constrain(lqr.k_omega * omg_r + lqr.k_theta * th + lqr.k_thetaDot * th_dot, -maxDrive, maxDrive);
  last_theta = theta;
  return val;
}
