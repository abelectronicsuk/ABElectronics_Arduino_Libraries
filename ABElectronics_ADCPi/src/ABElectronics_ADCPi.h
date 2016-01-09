/*
  ABEAdcpi.h - Library for ADC Pi board.
  Created by Brian Dorey, December 8, 2015.
  Released into the public domain.
*/

#ifndef ABElectronics_ADCPi_h
#define ABElectronics_ADCPi_h

#include "Arduino.h"


class ABElectronics_ADCPi
{
	public:
		// constructor
		ABElectronics_ADCPi(byte address, byte address2);
		// functions
		float readVoltage(int channel);
		long readRaw(int channel);
		void setPGA(int gain);
		void setConversionMode(int mode);
		void setBitRate(int rate);

	private:
		byte address1 = 0x68;  // default address for adc 1 on adc pi and delta-sigma pi
		byte address12 = 0x69;  // default address for adc 2 on adc pi and delta-sigma pi
		byte config1 = 0x9C;  // PGAx1, 18 bit, continuous conversion, channel 1
		int currentChannel1 = 1;  // channel variable for adc 1
		byte config2 = 0x9C;  // PGAx1, 18 bit, continuous-shot conversion, channel 1
		int currentChannel2 = 1;  // channel variable for adc2
		int bitRate = 18;  // current bitrate
		int conversionMode = 1; // Conversion Mode
		float pga = float(0.5);  // current pga setting
		float lsb = float(0.0000078125);  // default lsb value for 18 bit
		bool signBit = false;
		void setChannel(int channel);
		char updateByte(char byte, char bit, char value);

		void writeI2C(byte address, byte msg);
};
#endif