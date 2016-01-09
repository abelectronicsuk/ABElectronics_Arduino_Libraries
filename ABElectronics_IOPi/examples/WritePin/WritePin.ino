#include <Wire.h>
#include <ABElectronics_IOPi.h>

/*
================================================
ABElectronics IO Pi 32-Channel Port Expander - Write Pins Demo
Version 1.0 Created 08/01/2016
================================================
This example write the first 6 pins of bus 1 on the IO Pi board in a slow sequence. 

Initialise the IOPi device using the default addresses, you will need to
change the addresses if you have changed the jumpers on the IO Pi

*/

// Create instance of the IOPi 
ABElectronics_IOPi iopi(0x20);

void setup() {
  // Start the Wire bus
  Wire.begin();

  // Set port 0 and 1 to be outputs
  iopi.SetPortDirection(0, 0x00);
  iopi.SetPortDirection(1, 0x00);
  
  // turn off the pins
  iopi.WritePort(0, 0x00);
  iopi.WritePort(1, 0x00);

}

void loop() {
  // Turn on each pin in sequence with a 500ms delay between each command
  iopi.WritePin(0, 1);
  delay(500);
  iopi.WritePin(1, 1);
  delay(500);

  iopi.WritePin(2, 1);
  delay(500);

  iopi.WritePin(3, 1);
  delay(500);

  iopi.WritePin(4, 1);
  delay(500);

  iopi.WritePin(5, 1);
  delay(500);

  iopi.WritePin(6, 1);
  delay(500);

  // now turn off all pins on Port 0 and 1
  iopi.WritePort(0, 0x00);
  iopi.WritePort(1, 0x00);
  delay(500);
}
