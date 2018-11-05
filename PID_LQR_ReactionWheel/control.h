#ifndef CONTROL_H
#define CONTROL_H

float err;
float ref = 2.;
float dErr;
float sumErr = 0.0;
float lastErr = 0.0;
float theta = 0. , theta_dot=0. , omega_r = 0. ,  last_theta = 0;

int computePID(float pendPos);
int computeLQR(float th, float th_dot, float omg_r);

#endif
