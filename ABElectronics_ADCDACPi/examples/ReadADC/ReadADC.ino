#include <ABElectronics_ADCDACPi.h>

ABElectronics_ADCDACPi adcdac; // create ADCDACPi instance with I2C addresses.

void setup() {
   Serial.begin(9600);        
}

void loop() {
  // loop and display voltage on each of the inputs
  Serial.print("Channel 1: "); Serial.print(adcdac.readVoltage(1)); Serial.println(" V");
  Serial.print("Channel 2: "); Serial.print(adcdac.readVoltage(2)); Serial.println(" V");
  Serial.print("Raw 1: "); Serial.print(adcdac.readRaw(1)); Serial.println(" V");
  Serial.print("Raw 2: "); Serial.print(adcdac.readRaw(2)); Serial.println(" V");
  delay(500); 
}