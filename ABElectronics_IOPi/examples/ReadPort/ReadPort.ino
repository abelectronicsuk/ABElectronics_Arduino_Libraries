#include <Wire.h>
#include <ABElectronics_IOPi.h>

/*
================================================
ABElectronics IO Pi 32-Channel Port Expander - Read Port Demo
Version 1.0 Created 08/01/2016
================================================
This example reads port 0 and port 1 on a single chip on the IO Pi board.  The
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
  iopi.SetPortPullups(1, 0xFF);
}

void loop() {
  // Read Ports and print to the serial console
  Serial.print("Port 0:");
  Serial.println(iopi.ReadPort(0));

  Serial.print("Port 1:");
  Serial.println(iopi.ReadPort(1));
 
  delay(1000);
}