/*
  ABEAdcpi.h - Library for ADC Pi board.
  Created by Brian Dorey, December 8, 2015.
  Released into the public domain.
*/

#ifndef ABElectronics_ADCDACPi_h
#define ABElectronics_ADCDACPi_h

#include "Arduino.h"


class ABElectronics_ADCDACPi
{
	public:
		// constructor
		ABElectronics_ADCDACPi();
		// functions
		float readVoltage(int channel);
		long readRaw(int channel);
		void setDACVoltage(int channel, float voltage);
		void setDACRaw(int channel, short value);
	private:
		const int cs=10;
		const int cs1=9;
		double adcrefvoltage = 3.3;  //reference voltage for the ADC chip.
};
#endif