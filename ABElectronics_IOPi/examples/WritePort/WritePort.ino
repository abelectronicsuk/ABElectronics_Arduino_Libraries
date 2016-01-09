#include <Wire.h>
#include <ABElectronics_IOPi.h>

/*
================================================
ABElectronics IO Pi 32-Channel Port Expander - Write Port Demo
Version 1.0 Created 08/01/2016
================================================
This example writes a binary clock on bus 0 on the IO Pi board in a sequence. 

Connecting LEDs to the outputs will show the binary counting sequence.
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
  // Now we loop between 0 and 255 and write to port 0 to
  // make a simple binary counter.
  for (int x = 0; x  < 255; x++) {
    iopi.WritePort(0, x);
    delay(500);
  }
}