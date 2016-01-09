#include <ABElectronics_ADCDACPi.h>

ABElectronics_ADCDACPi adcdac; // create ADCDACPi instance with I2C addresses.

void setup() {
  // set the value using a raw value between 0 and 4095
  //adcdac.setDACRaw(1,4095);
  //adcdac.setDACRaw(2,2048);
  
  // set the value using a voltage between 0 and 2.048 
  adcdac.setDACVoltage(1,0.5); // set to 0.5V
  adcdac.setDACVoltage(2,1.75); // set to 1.75V
}

void loop() {
 
}