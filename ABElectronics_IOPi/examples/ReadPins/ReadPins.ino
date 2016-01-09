#include <Wire.h>
#include <ABElectronics_IOPi.h>


/*
================================================
ABElectronics IO Pi 32-Channel Port Expander - Read Pins Demo
Version 1.0 Created 08/01/2016
================================================
This example reads the first 8 pins of bus 1 on the IO Pi board.  The
internal pull-up resistors are enabled so each pin will read as 1 unless
the pin is connected to ground.

Initialise the IOPi device using the default addresses, you will need to
change the addresses if you have changed the jumpers on the IO Pi

*/

// Create instance of the IOPi 
ABElectronics_IOPi iopi(0x20);

void setup() {
  // Start the Wire bus
  Wire.begin();
  Serial.begin(9600);
  // Set port 0 and 1 to be inputs
  iopi.SetPortDirection(0, 0xFF);
  iopi.SetPortDirection(1, 0xFF);
  
  // enable the internal pull-up resistors
  iopi.SetPortPullups(0, 0xFF);

}

void loop() {
  // Read Pins and print to the serial console
  Serial.print("Pin 1:");
  Serial.println(iopi.ReadPin(1));

  Serial.print("Pin 2:");
  Serial.println(iopi.ReadPin(2));
  
  Serial.print("Pin 3:");
  Serial.println(iopi.ReadPin(3));

  Serial.print("Pin 4:");
  Serial.println(iopi.ReadPin(4));

  Serial.print("Pin 5:");
  Serial.println(iopi.ReadPin(5));
  
  Serial.print("Pin 6:");
  Serial.println(iopi.ReadPin(6));
  
  Serial.print("Pin 7:");
  Serial.println(iopi.ReadPin(7));
  
  Serial.print("Pin 8:");
  Serial.println(iopi.ReadPin(8));
  delay(1000);
}
