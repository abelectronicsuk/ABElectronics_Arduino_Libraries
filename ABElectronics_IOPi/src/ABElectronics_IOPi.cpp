#include <Arduino.h>
#include <Wire.h>
#include "ABElectronics_IOPi.h"

/// Note: Microchip recommends that pin 8 (GPA7) and pin 16 (GPB7) are used as outputs only.  
/// This change was made for revision D MCP23017 chips manufactured after June 2020. 
/// See the MCP23017 datasheet https://www.abelectronics.co.uk/docs/pdf/microchip-mcp23017.pdf for more information.  


ABElectronics_IOPi::ABElectronics_IOPi(byte icaddress)
{

  address = icaddress;


}

void ABElectronics_IOPi::SetPinDirection(byte pin, bool direction) {
	pin = (byte)(pin - 1);

            if (pin >= 0 && pin < 8)
            {
                port_a_dir = UpdateByte(port_a_dir, pin, direction);
                WriteI2CByte(IODIRA, port_a_dir);
            }
            else if (pin >= 8 && pin < 16)
            {
                port_b_dir = UpdateByte(port_b_dir, (byte)(pin - 8), direction);
                WriteI2CByte(IODIRB, port_b_dir);
            }
            else
            {
                // catch all for invalid pin
            }
        }
 /// <summary>
        /// Set the direction for an IO port.  You can control the direction of all 8 pins on a port by sending a single byte value.
        /// Each bit in the byte represents one pin so for example 0x0A would set pins 2 and 4 to inputs and all other pins to outputs.
        /// </summary>
        /// <param name="direction">Direction for all pins on the port.  1 = input, 0 = output</param>
        /// <param name="port">0 = pins 1 to 8, 1 = pins 9 to 16</param>
        void ABElectronics_IOPi::SetPortDirection(byte port, byte direction)
        {
            switch (port)
            {
                case 0:
                    WriteI2CByte(IODIRA, direction);
                    port_a_dir = direction;
                    break;
                case 1:
                    WriteI2CByte(IODIRB, direction);
                    port_b_dir = direction;
                    break;
                default:
                    // default
                    break;
            }

        }
        /// <summary>
        /// Set the internal 100K pull-up resistors for an individual pin
        /// </summary>
        /// <param name="pin">1 to 16</param>
        /// <param name="value">true = enabled, false = disabled</param>
        void ABElectronics_IOPi::SetPinPullup(byte pin, bool value)
        {
            pin = (byte)(pin - 1);

            if (pin >= 0 && pin < 8)
            {
                porta_pullup = UpdateByte(porta_pullup, pin, value);
                WriteI2CByte(GPPUA, porta_pullup);
            }
            else if (pin >= 8 && pin < 16)
            {
                portb_pullup = UpdateByte(portb_pullup, (byte)(pin - 8), value);
                WriteI2CByte(GPPUB, portb_pullup);
            }
            else
            {
                // default

            }
        }
        /// <summary>
        /// set the internal 100K pull-up resistors for the selected IO port
        /// </summary>
        /// <param name="port">0 = pins 1 to 8, 1 = pins 9 to 16</param>
        /// <param name="value">number between 0 and 255 or 0x00 and 0xFF</param>
        void ABElectronics_IOPi::SetPortPullups(byte port, byte value)
        {
            switch (port)
            {
                case 0:
                    porta_pullup = value;
                    WriteI2CByte(GPPUA, value);
                    break;
                case 1:
                    portb_pullup = value;
                    WriteI2CByte(GPPUB, value);
                    break;
                default:
                     // default
                     break;
            }
        }
        /// <summary>
        /// write to an individual pin
        /// </summary>
        /// <param name="pin">1 - 16</param>
        /// <param name="value">0 = logic low, 1 = logic high</param>
        void ABElectronics_IOPi::WritePin(byte pin, bool value)
        {
            pin = (byte)(pin - 1);
            if (pin >= 0 && pin < 8)
            {
                portaval = UpdateByte(portaval, pin, value);
                WriteI2CByte(GPIOA, portaval);
            }
            else if (pin >= 8 && pin < 16)
            {
                portbval = UpdateByte(portbval, (byte)(pin - 8), value);
                WriteI2CByte(GPIOB, portbval);
            }
            else
            {
                // default
            }
        }
        /// <summary>
        /// write to all pins on the selected port.
        /// </summary>
        /// <param name="port">0 = pins 1 to 8, 1 = pins 9 to 16</param>
        /// <param name="value">number between 0 and 255 or 0x00 and 0xFF</param>
        void ABElectronics_IOPi::WritePort(byte port, byte value)
        {
            switch (port)
            {
                case 0:
                    WriteI2CByte(GPIOA, value);
                    portaval = value;
                    break;
                case 1:
                    WriteI2CByte(GPIOB, value);
                    portbval = value;
                    break;
                default:
                     // default
                     break;
            }
        }
        /// <summary>
        /// read the value of an individual pin.
        /// </summary>
        /// <param name="pin">1 - 16</param>
        /// <returns>0 = logic level low, 1 = logic level high</returns>
        bool ABElectronics_IOPi::ReadPin(byte pin)
        {
            pin = (byte)(pin - 1);
            if (pin >= 0 && pin < 8)
            {
                portaval = ReadI2CByte(GPIOA);
                return CheckBit(portaval, pin);
            }
            else if (pin >= 8 && pin < 16)
            {
                portbval = ReadI2CByte(GPIOB);
                return CheckBit(portbval, (byte)(pin - 8));
            }
            else
            {
                 // default
            }
        }
        /// <summary>
        /// read all pins on the selected port.
        /// </summary>
        /// <param name="port">0 = pins 1 to 8, 1 = pins 9 to 16</param>
        /// <returns>returns number between 0 and 255 or 0x00 and 0xFF</returns>
        byte ABElectronics_IOPi::ReadPort(byte port)
        {
            switch (port)
            {
                case 0:
                    portaval = ReadI2CByte(GPIOA);
                    return portaval;
                case 1:
                    portbval = ReadI2CByte(GPIOB);
                    return portbval;
                default:
                    // default
                    break;
            }
        }
        /// <summary>
        /// invert the polarity of the pins on a selected port.
        /// </summary>
        /// <param name="port">0 = pins 1 to 8, 1 = pins 9 to 16</param>
        /// <param name="polarity">0x00 - 0xFF (0 = same logic state of the input pin, 1 = inverted logic state of the input pin)</param>

        void ABElectronics_IOPi::InvertPort(byte port, byte polarity)
        {
            switch (port)
            {
                case 0:
                    WriteI2CByte(IPOLA, polarity);
                    porta_polarity = polarity;
                    break;
                case 1:
                    WriteI2CByte(IPOLB, polarity);
                    portb_polarity = polarity;
                    break;
                default:
                     // default
                     break;
            }
        }
        /// <summary>
        /// invert the polarity of the selected pin.
        /// </summary>
        /// <param name="pin">1 to 16</param>
        /// <param name="polarity">False = same logic state of the input pin, True = inverted logic state of the input pin</param>
        void ABElectronics_IOPi::InvertPin(byte pin, bool polarity)
        {
            pin = (byte)(pin - 1);
            if (pin >= 0 && pin < 8)
            {
                porta_polarity = UpdateByte(portaval, pin, polarity);
                WriteI2CByte(IPOLA, porta_polarity);
            }
            else if (pin >= 8 && pin < 16)
            {
                portb_polarity = UpdateByte(portbval, (byte)(pin - 8), polarity);
                WriteI2CByte(IPOLB, portb_polarity);
            }
            else
            {
                 // default
            }
        }
        /// <summary>
        /// Sets the mirror status of the interrupt pins.
        /// </summary>
        /// <param name="value">0 = The INT pins are not mirrored. INTA is associated with PortA and INTB is associated with PortB. 1 = The INT pins are internally connected</param>
        void ABElectronics_IOPi::MirrorInterrupts(byte value)
        {
            switch (value)
            {
                case 0:
                    config = UpdateByte(config, 6, false);
                    WriteI2CByte(IOCON, config);
                    break;
                case 1:
                    config = UpdateByte(config, 6, true);
                    WriteI2CByte(IOCON, config);
                    break;
                default:
                     // default
                     break;
            }
        }
        /// <summary>
        /// This sets the polarity of the INT output pins
        /// </summary>
        /// <param name="value">1 = Active - high. 0 = Active - low.</param>
        void ABElectronics_IOPi::SetInterruptPolarity(byte value)
        {
            switch (value)
            {
                case 0:
                    config = UpdateByte(config, 1, false);
                    WriteI2CByte(IOCON, config);
                    break;
                case 1:
                    config = UpdateByte(config, 1, true);
                    WriteI2CByte(IOCON, config);
                    break;
                default:
                     // default
                     break;
            }
        }
        /// <summary>
        /// Sets the type of interrupt for each pin on the selected port. 1 = interrupt is fired when the pin matches the default value. 0 = the interrupt is fired on state change
        /// </summary>
        /// <param name="port">0 = pins 1 to 8, 1 = pins 9 to 16</param>
        /// <param name="value">number between 0 and 255 or 0x00 and 0xFF</param>
        void ABElectronics_IOPi::SetInterruptType(byte port, byte value)
        {
            switch (port)
            {
                case 0:
                    WriteI2CByte(INTCONA, value);
                    break;
                case 1:
                    WriteI2CByte(INTCONB, value);
                    break;
                default:
                     // default
                     break;
            }
        }
        /// <summary>
        /// These bits set the compare value for pins configured for interrupt-on-change on the selected port. If the associated pin level is the opposite from the register bit, an interrupt occurs.
        /// </summary>
        /// <param name="port">0 = pins 1 to 8, 1 = pins 9 to 16</param>
        /// <param name="value">number between 0 and 255 or 0x00 and 0xFF</param>
        void ABElectronics_IOPi::SetInterruptDefaults(byte port, byte value)
        {
            switch (port)
            {
                case 0:
                    WriteI2CByte(DEFVALA, value);
                    break;
                case 1:
                    WriteI2CByte(DEFVALB, value);
                    break;
                default:
                     // default
                     break;
            }
        }
        /// <summary>
        /// Enable interrupts for the pins on the selected port.
        /// </summary>
        /// <param name="port">0 = pins 1 to 8, 1 = pins 9 to 16</param>
        /// <param name="value">number between 0 and 255 or 0x00 and 0xFF</param>
        void ABElectronics_IOPi::SetInterruptOnPort(byte port, byte value)
        {
            switch (port)
            {
                case 0:
                    WriteI2CByte(GPINTENA, value);
                    intA = value;
                    break;
                case 1:
                    WriteI2CByte(GPINTENB, value);
                    intB = value;
                    break;
                default:
                     // default
                     break;
            }
        }
        /// <summary>
        /// Enable interrupts for the selected pin.
        /// </summary>
        /// <param name="pin">1 to 16</param>
        /// <param name="value">0 = interrupt disabled, 1 = interrupt enabled</param>
        void ABElectronics_IOPi::SetInterruptOnPin(byte pin, bool value)
        {

            pin = (byte)(pin - 1);
            if (pin >= 0 && pin < 8)
            {
                intA = UpdateByte(intA, pin, value);
                WriteI2CByte(GPINTENA, intA);
            }
            else if (pin >= 8 && pin < 16)
            {
                intB = UpdateByte(intB, (byte)(pin - 8), value);
                WriteI2CByte(GPINTENB, intB);
            }
            else
            {
                 // default

            }
        }
        /// <summary>
        /// read the interrupt status for the pins on the selected port.
        /// </summary>
        /// <param name="port">0 = pins 1 to 8, 1 = pins 9 to 16</param>
        byte ABElectronics_IOPi::ReadInterruptStatus(byte port)
        {
            switch (port)
            {
                case 0:
                    return ReadI2CByte(INTFA);
                case 1:
                    return ReadI2CByte(INTFB);
                default:
                     // default
                     break;
            }
        }
        /// <summary>
        /// read the value from the selected port at the time of the last interrupt trigger.
        /// </summary>
        /// <param name="port">0 = pins 1 to 8, 1 = pins 9 to 16</param>
        byte ABElectronics_IOPi::ReadInterruptCapture(byte port)
        {
            switch (port)
            {
                case 0:
                    return ReadI2CByte(INTCAPA);
                case 1:
                    return ReadI2CByte(INTCAPB);
                default:
                     // default
                     break;
            }
        }
        /// <summary>
        /// Reset the interrupts A and B to 0
        /// </summary>
        void ABElectronics_IOPi::ResetInterrupts()
        {
            ReadInterruptCapture(0);
            ReadInterruptCapture(1);
        }

		/// <summary>
        /// Updates the value of a single bit within a byte and returns the updated byte
        /// </summary>
        /// <param name="value">The byte to update</param>
        /// <param name="position">Position of the bit to change</param>
        /// <param name="bitstate">The new bit value</param>
        /// <returns></returns>

	char ABElectronics_IOPi::UpdateByte(char byte, char bit, char value)
	{ /* internal method for setting the value of a single bit within a byte */
		if (value == 0) {
			return (byte &= ~(1 << bit));
	  	} else {
		return (byte |= 1 << bit);
	  	}

	}



        /// <summary>
        /// Checks the value of a single bit within a byte
        /// </summary>
        /// <param name="value">The value to query</param>
        /// <param name="position">The bit position within the byte</param>
        /// <returns></returns>
        bool ABElectronics_IOPi::CheckBit(byte value, byte position)
        {
            // internal method for reading the value of a single bit within a byte
            return (value & (1 << position)) != 0;
        }

        bool ABElectronics_IOPi::CheckIntBit(int value, byte position)
        {
            // internal method for reading the value of a single bit within a byte
            return (value & (1 << position)) != 0;
        }



        /// <summary>
        /// Writes a single byte to an I2C device.
        /// </summary>
        /// <param name="bus">I2C device</param>
        /// <param name="register">Address register</param>
        /// <param name="value">Value to write to the register</param>
        void ABElectronics_IOPi::WriteI2CByte(byte value1, byte value)
        {
            Wire.beginTransmission(address);
			Wire.write(value1);
			Wire.write(value);
  			Wire.endTransmission();

        }

        /// <summary>
        /// Read a single byte from an I2C device
        /// </summary>
        /// <param name="bus">I2C device</param>
        /// <param name="register">Address register to read from</param>
        /// <returns></returns>
        byte ABElectronics_IOPi::ReadI2CByte(byte value1)
        {
			Wire.beginTransmission(address);
			Wire.write(value1);
   			Wire.endTransmission();

			byte val = 0x00;
			Wire.requestFrom((int)address, 1);
			while (Wire.available() <= 0) {

			}
			  val = Wire.read();
   			Wire.endTransmission();

            return val;
        }
