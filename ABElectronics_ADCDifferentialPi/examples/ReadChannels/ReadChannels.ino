#include <Wire.h>
#include <ABElectronics_ADCDifferentialPi.h>

ABElectronics_ADCDifferentialPi adc(0x68, 0x69); // create ABElectronics_ADCDifferentialPi instance with I2C addresses.


void setup() {
  
  Serial.begin(9600);  
  // Start Wire and set the ADC object bit rate and PGA (gain)
  Wire.begin(); 
  adc.setBitRate(18);
  adc.setPGA(1);
}

void loop() {
  // loop and display voltage on each of the 8 inputs
  
  Serial.print("Channel 1: "); Serial.print(adc.readVoltage(1)); Serial.println(" V");
  Serial.print("Channel 2: "); Serial.print(adc.readVoltage(2)); Serial.println(" V");
  Serial.print("Channel 3: "); Serial.print(adc.readVoltage(3)); Serial.println(" V");
  Serial.print("Channel 4: "); Serial.print(adc.readVoltage(4)); Serial.println(" V");
  Serial.print("Channel 5: "); Serial.print(adc.readVoltage(5)); Serial.println(" V");
  Serial.print("Channel 6: "); Serial.print(adc.readVoltage(6)); Serial.println(" V");
  Serial.print("Channel 7: "); Serial.print(adc.readVoltage(7)); Serial.println(" V");
  Serial.print("Channel 8: "); Serial.print(adc.readVoltage(8)); Serial.println(" V");
}
