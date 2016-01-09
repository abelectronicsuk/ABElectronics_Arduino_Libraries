/*
  ABElectronics_ADCDifferentialPi.h - Library for ADC Differential Pi board.
  Created by Brian Dorey, December 8, 2015.
  Released into the public domain.
*/

#ifndef ABElectronics_ADCDifferentialPi_h
#define ABElectronics_ADCDifferentialPi_h

#include "Arduino.h"


class ABElectronics_ADCDifferentialPi
{
	public:
		// constructor
		ABElectronics_ADCDifferentialPi(byte address, byte address2);
		// functions
		float readVoltage(int channel);
		long readRaw(int channel);
		void setPGA(int gain);
		void setConversionMode(int mode);
		void setBitRate(int rate);

	private:
		byte address1 = 0x68;  // default address for adc 1 on ADC Differential Pi
		byte address12 = 0x69;  // default address for ADC Differential Pi
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
		//bool checkBit(char byte, char bit);

		void writeI2C(byte address, byte msg);
};
#endif