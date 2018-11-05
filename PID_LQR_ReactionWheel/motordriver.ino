#include "motordriver.h"

void setupPWM16() {
  DDRB |= _BV(PB1) | _BV(PB2);        /* set pins as outputs */
  TCCR1A = _BV(COM1A1) | _BV(COM1B1)  /* non-inverting PWM */
           | _BV(WGM11);                   /* mode 14: fast PWM, TOP=ICR1 */
  TCCR1B = _BV(WGM13) | _BV(WGM12);                    
  ICR1 = icr;
  TCCR1B = TCCR1B & 0B11111000 | 0B00000001;                     
}                

void analogWrite16(uint8_t pin, uint16_t val) {
  switch (pin) {
    case  9: OCR1A = val; break;
    case  10: OCR1B = val; break;
  }
}

void motorWheelDrive(byte dir, uint16_t pwm) {
  //Serial.print("pwm = "); Serial.println(pwm);
  switch (dir) {
    case 0: //turn clockwise
      analogWrite16(LPWM_Output, 0);
      analogWrite16(RPWM_Output, pwm);
      //Serial.println("Clockwise");
      break;
    case 1: //turn anti-clockwise
      analogWrite16(RPWM_Output, 0);
      analogWrite16(LPWM_Output, pwm);
      //Serial.println("Anti-Clockwise");
      break;
    case 2: //stop
      analogWrite16(RPWM_Output, 0);
      analogWrite16(LPWM_Output, 0);
      break;

  }
}

void motor_stop(){
  motorWheelDrive(2,0);  
}
