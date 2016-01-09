#include <Arduino.h>
#include <Wire.h>
#include "ABElectronics_ADCPi.h"

char ABElectronics_ADCPi::updateByte(char byte, char bit, char value) {
  /*
    internal method for setting the value of a single bit within a byte
  */
  if (value == 0) {
    return (byte &= ~(1 << bit));

  } else {
    return (byte |= 1 << bit);
  }

}


ABElectronics_ADCPi::ABElectronics_ADCPi(byte address, byte address2)
{

  address1 = address;
  address12 = address2;

}


float ABElectronics_ADCPi::readVoltage(int channel) {
  // returns the voltage from the selected adc channel - channels 1 to 8
  long raw = readRaw(channel);
  // if (signBit) {
  //    return float(0.0);  // returned a negative voltage so return 0
  // } else{
  float voltage = float((raw * (lsb / pga)) * 2.471);
  return float(voltage);
  //  }
}

long ABElectronics_ADCPi::readRaw(int channel) {
  // reads the raw value from the selected adc channel - channels 1 to 8
  byte h = 0;
  byte l = 0;
  byte m = 0;
  byte s = 0;
  byte sendconfig = 0x00;
  byte address = 0x00;
  long t = 0;

  // get the config and i2c address for the selected channel
  setChannel(channel);
  if (channel < 5) {
    sendconfig = config1;
    address = address1;
  } else {
    sendconfig = config2;
    address = address12;
  }
  writeI2C(address, sendconfig);


  // if the conversion mode is set to one-shot update the ready bit to 1
  if (conversionMode == 0) {
    sendconfig = bitWrite(sendconfig, 7, 1);
    writeI2C(address, sendconfig);
    sendconfig = bitWrite(sendconfig, 7, 0);
  }

  // timeout counter

  int bytestoread = 4;
  if (bitRate != 18) {
    bytestoread = 4;
  }

  do {
    // loop until a value is available
    Wire.requestFrom((uint8_t)address, (uint8_t)bytestoread);

    if (Wire.available() != bytestoread) {
      Serial.println("read failed");
      return false;
    }

    if (bitRate == 18) {
      h = Wire.read();
      m = Wire.read();
      l = Wire.read();
      s = Wire.read();
    }
    else {
      h = Wire.read();
      m = Wire.read();
      s = Wire.read();
    }
    if (bitRead(s, 7) == 0) {
      break;
    }
  } while (1);

  // extract the returned bytes and combine in the correct order
  if (bitRate == 18) {
    t = h;
    t &= 0b00000011;
    t = t << 8;
    t |= m;
    t = t << 8;
    t |= l;

    signBit = bitRead(t, 17);
    if (signBit) {
      t = updateByte(t, 17, 0);
    }

  }
  if (bitRate == 16) {
    t = (h << 8) | m;

    signBit = bitRead(t, 15);
    if (signBit) {
      t = updateByte(t, 15, 0);
    }
  }
  if (bitRate == 14) {
    t = h;
    t &= 0b00111111;
    t = t << 8;
    t |= m;

    signBit = bitRead(t, 13);
    if (signBit) {
      t = updateByte(t, 13, 0);
    }
  }
  if (bitRate == 12) {
    t = h;
    t &= 0b00001111;
    t = t << 8;
    t |= m;

    signBit = bitRead(t, 11);
    if (signBit) {
      t = updateByte(t, 11, 0);
    }
  }
  // return raw reading value
  return t;
}

void ABElectronics_ADCPi::setChannel(int channel) {
  //internal method for updating the config to the selected channel
  if (channel < 5) {
    if (channel != currentChannel1) {
      if (channel == 1) {
        config1 = bitWrite(config1, 5, 0);
        config1 = bitWrite(config1, 6, 0);
        currentChannel1 = 1;
      }
      if (channel == 2) {
        config1 = bitWrite(config1, 5, 1);
        config1 = bitWrite(config1, 6, 0);
        currentChannel1 = 2;
      }
      if (channel == 3) {
        config1 = bitWrite(config1, 5, 0);
        config1 = bitWrite(config1, 6, 1);
        currentChannel1 = 3;
      }
      if (channel == 4) {
        config1 = bitWrite(config1, 5, 1);
        config1 = bitWrite(config1, 6, 1);
        currentChannel1 = 4;
      }
    }
  } else {
    if (channel != currentChannel2) {
      if (channel == 5) {
        config2 = bitWrite(config2, 5, 0);
        config2 = bitWrite(config2, 6, 0);
        currentChannel2 = 5;
      }
      if (channel == 6) {
        config2 = bitWrite(config2, 5, 1);
        config2 = bitWrite(config2, 6, 0);
        currentChannel2 = 6;
      }
      if (channel == 7) {
        config2 = bitWrite(config2, 5, 0);
        config2 = bitWrite(config2, 6, 1);
        currentChannel2 = 7;
      }
      if (channel == 8) {
        config2 = bitWrite(config2, 5, 1);
        config2 = bitWrite(config2, 6, 1);
        currentChannel2 = 8;
      }
    }
  }
}
void ABElectronics_ADCPi::setPGA(int gain) {
  // PGA gain selection
  //1 = 1x
  // 2 = 2x
  // 4 = 4x
  // 8 = 8x

  if (gain == 1) {
    config1 = bitWrite(config1, 0, 0);
    config1 = bitWrite(config1, 1, 0);
    config2 = bitWrite(config2, 0, 0);
    config2 = bitWrite(config2, 1, 0);
    pga = 0.5;
  }
  if (gain == 2) {
    config1 = bitWrite(config1, 0, 1);
    config1 = bitWrite(config1, 1, 0);
    config2 = bitWrite(config2, 0, 1);
    config2 = bitWrite(config2, 1, 0);
    pga = 1;
  }
  if (gain == 4) {
    config1 = bitWrite(config1, 0, 0);
    config1 = bitWrite(config1, 1, 1);
    config2 = bitWrite(config2, 0, 0);
    config2 = bitWrite(config2, 1, 1);
    pga = 2;
  }
  if (gain == 8) {
    config1 = bitWrite(config1, 0, 1);
    config1 = bitWrite(config1, 1, 1);
    config2 = bitWrite(config2, 0, 1);
    config2 = bitWrite(config2, 1, 1);
    pga = 4;
  }

  writeI2C(address1, config1);
  writeI2C(address12, config2);
}
void ABElectronics_ADCPi::setBitRate(int rate) {
  //
  //sample rate and resolution
  //12 = 12 bit (240SPS max)
  //14 = 14 bit (60SPS max)
  //16 = 16 bit (15SPS max)
  //18 = 18 bit (3.75SPS max)
  //

  if (rate == 12) {
    config1 = bitWrite(config1, 2, 0);
    config1 = bitWrite(config1, 3, 0);
    config2 = bitWrite(config2, 2, 0);
    config2 = bitWrite(config2, 3, 0);
    bitRate = 12;
    lsb = 0.0005;
  }
  if (rate == 14) {
    config1 = bitWrite(config1, 2, 1);
    config1 = bitWrite(config1, 3, 0);
    config2 = bitWrite(config2, 2, 1);
    config2 = bitWrite(config2, 3, 0);
    bitRate = 14;
    lsb = 0.000125;
  }
  if (rate == 16) {
    config1 = bitWrite(config1, 2, 0);
    config1 = bitWrite(config1, 3, 1);
    config2 = bitWrite(config2, 2, 0);
    config2 = bitWrite(config2, 3, 1);
    bitRate = 16;
    lsb = 0.00003125;
  }
  if (rate == 18) {
    config1 = bitWrite(config1, 2, 1);
    config1 = bitWrite(config1, 3, 1);
    config2 = bitWrite(config2, 2, 1);
    config2 = bitWrite(config2, 3, 1);
    bitRate = 18;
    lsb = 0.0000078125;
  }

  writeI2C(address1, config1);
  writeI2C(address12, config2);
}

void ABElectronics_ADCPi::setConversionMode(int mode) {

  // conversion mode for adc
  // 0 = One shot conversion mode
  // 1 = Continuous conversion mode

  if (mode == 0) {
    config1 = bitWrite(config1, 4, 0);
    config2 = bitWrite(config2, 4, 0);
    conversionMode = 0;
  }
  if (mode == 1) {
    config1 = bitWrite(config1, 4, 1);
    config2 = bitWrite(config2, 4, 1);
    conversionMode = 1;
  }
}

void ABElectronics_ADCPi::writeI2C(byte address, byte msg)
{
  // Write byte value to Wire bus, uncommend lines below to debug values being sent
  //Serial.println(address,HEX);
  // Serial.println(msg,HEX);
  Wire.beginTransmission(address);
  Wire.write(msg);
  Wire.endTransmission();

}