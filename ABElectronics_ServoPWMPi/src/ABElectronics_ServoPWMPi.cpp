#include <Arduino.h>
#include <Wire.h>

#include "ABElectronics_ServoPWMPi.h"
#if defined(ARDUINO_SAM_DUE)
#define WIRE Wire1
#else
#define WIRE Wire
#endif

ABElectronics_ServoPWMPi::ABElectronics_ServoPWMPi(byte i2caddress)
{
  address = i2caddress;
}

void ABElectronics_ServoPWMPi::begin()
{
  WIRE.begin();
  // Reset PWM Chip
  WriteI2CByte(MODE1, 0x00);
}

/// <summary>
/// Set the PWM frequency in hertz
/// </summary>
/// <param name="freq"></param>
/// <example>servopi.SetPWMFreqency(60);</example>
void ABElectronics_ServoPWMPi::SetPWMFreqency(int freq)
{
  double scaleval = 25000000.0; // 25MHz
  scaleval /= 4096.0; // 12-bit
  scaleval /= freq;
  scaleval -= 1.0;
  double prescale = floor(scaleval + 0.5);
  byte oldmode = ReadI2CByte(MODE1);
  byte newmode = (byte)((oldmode & 0x7F) | 0x10);
  WriteI2CByte(MODE1, newmode);
  WriteI2CByte(PRE_SCALE, (byte)(floor(prescale)));
  WriteI2CByte(MODE1, oldmode);
  WriteI2CByte(MODE1, (byte)(oldmode | 0x80));
}

/// <summary>
/// Set the PWM output on a single channel
/// </summary>
/// <param name="channel">1 to 16</param>
/// <param name="on">Value between 0 and 4096</param>
/// <param name="off">Value between 0 and 4096</param>
/// <example>servopi.SetPWM(1,512,1024);</example>
void ABElectronics_ServoPWMPi::SetPWM(byte channel, short on, short off)
{
  channel = (byte)(channel - 1);
  WriteI2CByte((byte)(LED0_ON_L + (4 * channel)), (byte)(on & 0xFF));
  WriteI2CByte((byte)(LED0_ON_H + (4 * channel)), (byte)(on >> 8));
  WriteI2CByte((byte)(LED0_OFF_L + (4 * channel)), (byte)(off & 0xFF));
  WriteI2CByte((byte)(LED0_OFF_H + (4 * channel)), (byte)(off >> 8));
}

/// <summary>
/// Set PWM output on all channels
/// </summary>
/// <param name="on">Value between 0 and 4096</param>
/// <param name="off">Value between 0 and 4096</param>
/// <example>servopi.SetAllPWM(512,1024);</example>
void ABElectronics_ServoPWMPi::SetAllPWM(short on, short off)
{
  WriteI2CByte(ALL_LED_ON_L, (byte)(on & 0xFF));
  WriteI2CByte(ALL_LED_ON_H, (byte)(on >> 8));
  WriteI2CByte(ALL_LED_OFF_L, (byte)(off & 0xFF));
  WriteI2CByte(ALL_LED_OFF_H, (byte)(off >> 8));
}

void ABElectronics_ServoPWMPi::writeI2C(byte address, byte msg)
{
  Wire.beginTransmission(address);
  Wire.write(msg);
  Wire.endTransmission();
}

/// <summary>
/// Writes a single byte to an I2C device.
/// </summary>
/// <param name="bus">I2C device</param>
/// <param name="register">Address register</param>
/// <param name="value">Value to write to the register</param>
void ABElectronics_ServoPWMPi::WriteI2CByte(byte value1, byte value)
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
byte ABElectronics_ServoPWMPi::ReadI2CByte(byte value1)
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