/*
  ABElectronics_IOPi.h - Library for IOPi board.
  Created by Brian Dorey, January 7th 2016.
  Released into the public domain.
*/

/// Note: Microchip recommends that pin 8 (GPA7) and pin 16 (GPB7) are used as outputs only.  
/// This change was made for revision D MCP23017 chips manufactured after June 2020. 
/// See the MCP23017 datasheet https://www.abelectronics.co.uk/docs/pdf/microchip-mcp23017.pdf for more information. 

#ifndef ABElectronics_IOPi_h
#define ABElectronics_IOPi_h

#include "Arduino.h"



class ABElectronics_IOPi
{
	public:
		// constructor
		ABElectronics_IOPi(byte address);
		// functions
		void Connect();
		void SetPinDirection(byte pin, bool direction);
		void SetPortDirection(byte port, byte direction);
		void SetPinPullup(byte pin, bool value);
		void SetPortPullups(byte port, byte value);
		void WritePin(byte pin, bool value);
		void WritePort(byte port, byte value);
		bool ReadPin(byte pin);
		byte ReadPort(byte port);
		void InvertPort(byte port, byte polarity);
		void InvertPin(byte pin, bool polarity);
		void MirrorInterrupts(byte value);
		void SetInterruptPolarity(byte value);
		void SetInterruptType(byte port, byte value);
		void SetInterruptDefaults(byte port, byte value);
		void SetInterruptOnPort(byte port, byte value);
		void SetInterruptOnPin(byte pin, bool value);
		byte ReadInterruptStatus(byte port);
		byte ReadInterruptCapture(byte port);
		void ResetInterrupts();
	private:
		bool isConnected;
		// Define registers values from datasheet
		byte IODIRA = 0x00;  // IO direction A - 1= input 0 = output
		byte IODIRB = 0x01;  // IO direction B - 1= input 0 = output
		byte IPOLA = 0x02; // Input polarity A - If a bit is set, the corresponding GPIO register bit will reflect the inverted value on the pin.
		byte IPOLB = 0x03; // Input polarity B - If a bit is set, the corresponding GPIO register bit will reflect the inverted value on the pin.
		byte GPINTENA = 0x04; // The GPINTEN register controls the interrupt-on-change feature for each pin on port A.
		byte GPINTENB = 0x05; // The GPINTEN register controls the interrupt-on-change feature for each pin on port B.
		byte DEFVALA = 0x06; // Default value for port A - These bits set the compare value for pins configured for interrupt-on-change. If the associated pin level is the opposite from the register bit, an interrupt occurs.
		byte DEFVALB = 0x07; // Default value for port B - These bits set the compare value for pins configured for interrupt-on-change. If the associated pin level is the opposite from the register bit, an interrupt occurs.
		byte INTCONA = 0x08; // Interrupt control register for port A.  If 1 interrupt is fired when the pin matches the default value, if 0 the interrupt is fired on state change
		byte INTCONB = 0x09; // Interrupt control register for port B.  If 1 interrupt is fired when the pin matches the default value, if 0 the interrupt is fired on state change
		byte IOCON = 0x0A;  // see datasheet for configuration register
		byte GPPUA = 0x0C;  // pull-up resistors for port A
		byte GPPUB = 0x0D;  // pull-up resistors for port B
		byte INTFA = 0x0E; // The INTFA register reflects the interrupt condition on the port A pins of any pin that is enabled for interrupts. A set bit indicates that the associated pin caused the interrupt.
		byte INTFB = 0x0F; // The INTFB register reflects the interrupt condition on the port B pins of any pin that is enabled for interrupts. A set bit indicates that the associated pin caused the interrupt.
		byte INTCAPA = 0x10; // The INTCAP register captures the GPIO port A value at the time the interrupt occurred.
		byte INTCAPB = 0x11; // The INTCAP register captures the GPIO port B value at the time the interrupt occurred.
		byte GPIOA = 0x12; // data port A
		byte GPIOB = 0x13;  // data port B
		byte OLATA = 0x14; // output latches A
		byte OLATB = 0x15; // output latches B

		// variables
		byte port_a_dir = 0x00;  // port a direction
		byte port_b_dir = 0x00;  // port b direction
		byte portaval = 0x00;  // port a value
		byte portbval = 0x00;  // port b value
		byte porta_pullup = 0x00; // port a pull-up resistors
		byte portb_pullup = 0x00; // port a pull-up resistors
		byte porta_polarity = 0x00;  // input polarity for port a
		byte portb_polarity = 0x00; // input polarity for port b
		byte intA = 0x00; // interrupt control for port a
		byte intB = 0x00; // interrupt control for port a

        byte config = 0x22; // initial configuration - see IOCON page in the MCP23017 datasheet for more information.
		byte address = 0x20;
		char updateByte(char byte, char bit, char value);
		byte ReadI2CByte(byte value1);
		void WriteI2CByte(byte value1, byte value);
		bool CheckIntBit(int value, byte position);
		bool CheckBit(byte value, byte position);
		char UpdateByte(char byte, char bit, char value);
};
#endif