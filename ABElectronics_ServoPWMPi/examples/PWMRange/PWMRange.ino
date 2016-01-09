#include <ABElectronics_ServoPWMPi.h>

// This demo shows how to set a 1KHz output frequency and change the pulse width 
// between the minimum and maximum values

// create ServoPWMPi instance with I2C addresses.
ABElectronics_ServoPWMPi servo(0x40);


void setup() {

  // Start Servo PWM instance
  servo.begin();
  // set pwm frequency to 1000Hz
  servo.SetPWMFreqency(1000); 

}

void loop() {
  for (int x = 1; x < 4095; x = x + 5) {
   servo.SetPWM(1, 0, x);
    delay(10);
  }
   for (int x = 4095; x > 1; x = x - 5) {
   servo.SetPWM(1, 0, x);
    delay(10);
  }
}
