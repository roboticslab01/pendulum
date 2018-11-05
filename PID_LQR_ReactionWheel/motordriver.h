#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

uint8_t RPWM_Output = 9;
uint8_t LPWM_Output = 10;
uint16_t icr = 0x03ff; //pwm 10 bit 0b0011 1111 1111

void setupPWM16();
void analogWrite16(uint8_t pin, uint16_t val);
void motorWheelDrive(byte dir, uint16_t pwm);
void motor_stop();


#endif
