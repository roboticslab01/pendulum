#ifndef DRIVER_H
#define DRIVER_H

uint8_t LPWM_Output = 11;
uint8_t RPWM_Output = 12;
uint16_t icr = 0x03ff; //pwm 10 bit 0b0011 1111 1111

void setupPWM16();
void analogWrite16(uint8_t pin, uint16_t val);
void motorDrive(byte dir, uint16_t pwm);
void motor_stop();

#endif
