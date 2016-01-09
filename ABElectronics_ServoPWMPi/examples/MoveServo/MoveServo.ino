#include <ABElectronics_ServoPWMPi.h>

// create ServoPWMPi instance with I2C addresses.
ABElectronics_ServoPWMPi servo(0x40);


void setup() {
  // Start Servo PWM instance
  servo.begin();
  // set pwm frequency to 60hz
  servo.SetPWMFreqency(60); 

}

void loop() {
  // loop through three servo postions and repeat.
   servo.SetPWM(1, 0, 250);
   delay(400);
   servo.SetPWM(1, 0, 400);
   delay(400);
   servo.SetPWM(1, 0, 500);
   delay(400);

}