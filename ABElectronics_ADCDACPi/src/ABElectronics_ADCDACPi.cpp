#include <Arduino.h>
#include "SPI.h"
#include "ABElectronics_ADCDACPi.h"

ABElectronics_ADCDACPi::ABElectronics_ADCDACPi()
{
	pinMode(SS, OUTPUT);
	pinMode(cs1, OUTPUT);// make sure slave select is an output
	SPI.setClockDivider( SPI_CLOCK_DIV4 ); // slow the SPI bus down
	SPI.begin();                           // SPI at the ready
}

float ABElectronics_ADCDACPi::readVoltage(int channel) {
  // returns the voltage from the selected adc channel - channels 1 to 2
  long raw = readRaw(channel);

  float voltage = float((adcrefvoltage / 4096) * raw);
  return float(voltage);
  //  }
}

long ABElectronics_ADCDACPi::readRaw(int channel) {
  // reads the raw value from the selected adc channel - channels 1 to 2
	byte commandbits = B00001101;
	unsigned int b1 = 0;
	unsigned int b2 = 0;
	commandbits|=((channel-1)<<1);         // update the command bit to select either ch 1 or 2
	digitalWrite(cs, LOW);
	SPI.transfer(commandbits);
	const int hi = SPI.transfer(b1);       // read back the result high byte
	const int lo = SPI.transfer(b2);       // then the low byte
	digitalWrite(cs, HIGH);
	return (short)(((hi & 0x0F) << 8) + (lo)); // combine the bytes to create the return raw value
}


void ABElectronics_ADCDACPi::setDACVoltage(int channel, float voltage) {
  // Set the DAC voltage
  // Voltage can be between 0 and 2.047 volts
  short rawval = (short)((voltage / 2.048) * 4096); // convert the voltage into a raw value
  setDACRaw(channel, rawval);

}

void ABElectronics_ADCDACPi::setDACRaw(int channel, short value) {
	// set the raw value for the selected dac channel - channels 1 to 2
	// raw value between 0 and 4095
	byte lowByte = (byte)(value & 0xff);
	byte highByte = (byte)(((value >> 8) & 0xff) | (channel - 1) << 7 | 0x1 << 5 | 1 << 4);

	digitalWrite(cs1, LOW);
	SPI.transfer(highByte);
	SPI.transfer(lowByte);
	digitalWrite(cs1, HIGH);

}
