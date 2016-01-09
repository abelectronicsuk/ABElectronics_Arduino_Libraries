/*
  ABEServoPWMPi.h - Library for Servo PWM Pi board.
  Created by Brian Dorey, December 8, 2015.
  Released into the public domain.
*/

#ifndef ABElectronics_ServoPWMPi_h
#define ABElectronics_ServoPWMPi_h

#include "Arduino.h"


class ABElectronics_ServoPWMPi
{
	public:
		// constructor
		ABElectronics_ServoPWMPi(byte address);
		// functions
		void SetPWMFreqency(int freq);
		void SetPWM(byte channel, short on, short off);
		void SetAllPWM(short on, short off);
		void begin();

	private:
		byte address = 0x40;  // default address for
		byte MODE1 = 0x00;
        byte MODE2 = 0x01;
        byte SUBADR1 = 0x02;
        byte SUBADR2 = 0x03;
        byte SUBADR3 = 0x04;
        byte ALLCALLADR = 0x05;
        byte LED0_ON_L = 0x06;
        byte LED0_ON_H = 0x07;
        byte LED0_OFF_L = 0x08;
        byte LED0_OFF_H = 0x09;
        byte ALL_LED_ON_L = 0xFA;
        byte ALL_LED_ON_H = 0xFB;
        byte ALL_LED_OFF_L = 0xFC;
        byte ALL_LED_OFF_H = 0xFD;
        byte PRE_SCALE = 0xFE;

		void WriteI2CByte(byte value1, byte value);
		void writeI2C(byte address, byte msg);
		byte ReadI2CByte(byte value1);
};
#endif