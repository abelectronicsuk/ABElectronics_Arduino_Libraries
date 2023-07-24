#include <Arduino.h>
#include "SPI.h"
#include "ABElectronics_ADCDACPi.h"

static byte adctx[] = { 0x01, 0x80, 0x00 }; // transmit buffer for the ADC

#define SPI_ADC_CLOCK 1100000
#define SPI_DAC_CLOCK 20000000

ABElectronics_ADCDACPi::ABElectronics_ADCDACPi()
{
	pinMode(SS, OUTPUT);
	pinMode(cs1, OUTPUT);// make sure slave select is an output
	SPI.begin();                           // SPI at the ready
}

float ABElectronics_ADCDACPi::readVoltage(int channel) {
  // returns the voltage from the selected adc channel - channels 1 to 2
  long raw = readRaw(channel);

  float voltage = float((adcrefvoltage / 4096) * raw);
  return float(voltage);

}

long ABElectronics_ADCDACPi::readRaw(int channel) {
  // reads the raw value from the selected adc channel - channels 1 to 2
	if (channel == 1) {
	    adctx[1] = 0x80;
	  } else if (channel == 2) {
	    adctx[1] = 0xC0;
	  } else {
	    return (0);
	  }

	  digitalWrite(cs, LOW);
	  SPI.beginTransaction(SPISettings(SPI_ADC_CLOCK, MSBFIRST, SPI_MODE0));
	  SPI.transfer(adctx[0]);
	  int hi = SPI.transfer(adctx[1]);       // read back the result high byte
	  int lo = SPI.transfer(adctx[2]);       // then the low byte
	  SPI.endTransaction();
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
	SPI.beginTransaction(SPISettings(SPI_DAC_CLOCK, MSBFIRST, SPI_MODE0));
	SPI.transfer(highByte);
	SPI.transfer(lowByte);
	SPI.endTransaction();
	digitalWrite(cs1, HIGH);

}
