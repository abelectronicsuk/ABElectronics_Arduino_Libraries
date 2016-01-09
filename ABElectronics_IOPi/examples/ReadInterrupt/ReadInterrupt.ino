#include <Wire.h>
#include <ABElectronics_IOPi.h>


/*
================================================
ABElectronics IO Pi 32-Channel Port Expander - Read Interrupt demo
Version 1.0 Created 08/01/2016
================================================
The interrupts will be enabled and set so that a voltage applied to
pins 1 and 16 will trigger INT A and B respectively.
using the read_interrupt_capture or read_port methods will
reset the interrupts

Initialise the IOPi device using the default addresses, you will need to
change the addresses if you have changed the jumpers on the IO Pi

*/

// Create instance of the IOPi 
ABElectronics_IOPi iopi(0x20);
ABElectronics_IOPi iopib(0x21);

void setup() {
  // Start the Wire bus
  Wire.begin();
  Serial.begin(9600);
  
  // Set all pins on bus 2 to be inputs with internal pull-ups disabled.
  iopib.SetPortPullups(0, 0x00);
  iopib.SetPortPullups(1, 0x00);
  
  iopib.SetPortDirection(0, 0xFF);
  iopib.SetPortDirection(1, 0xFF);
  
  // Set the interrupt polarity to be active high and mirroring disabled, so
  // pins 1 to 8 trigger INT A and pins 9 to 16 trigger INT B
  iopib.SetInterruptPolarity(1);
  iopib.MirrorInterrupts(0);
  
  // Set the interrupts default value to trigger when 5V is applied to pins 1
  // and 16
  iopib.SetInterruptDefaults(0, 0x01);
  iopib.SetInterruptDefaults(0, 0x80);
  
  // Set the interrupt type to be 1 for ports A and B so an interrupt is
  // fired when the pin matches the default value
  iopib.SetInterruptType(0, 1);
  iopib.SetInterruptType(1, 1);
  
  // Enable interrupts for pins 1 and 16
  iopib.SetInterruptOnPin(1, 1);
  iopib.SetInterruptOnPin(16, 1);


}

void loop() {
  // Read Pins and print to the serial console
  Serial.println(iopib.ReadInterruptCapture(0));
  Serial.println(iopib.ReadInterruptCapture(1));
  
 
  delay(100);
}
