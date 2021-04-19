// -------------------------------------------------------------------------------------
// incluir header para classe register
#include "Register.h"
#include "Arduino.h"

// defines what pins are being used, for data, clk and output pulse
Register::Register(int dataPin, int clkPin, int attOutputsPin){
  _validValues = true;
  _value = 0x00;
  _pinsMode = _3PINS;
  _triState = true;

  if (dataPin == clkPin || dataPin == attOutputsPin || clkPin == attOutputsPin){
    // set an 'error' value, due to the repeated values used
    _validValues = false;
    _pinsMode = _ERROR;
    setPins(-1, -1, -1, -1, -1);
  }
  
  else{
    // set the pins used, makes them output and starts them in the default value
    setPins(dataPin, clkPin, attOutputsPin, -1, -1);
    pinMode(dataPin, 1);
    pinMode(clkPin, 1);
    pinMode(attOutputsPin, 1);
    digitalWrite(dataPin, 0);
    digitalWrite(clkPin, 0);
    digitalWrite(attOutputsPin, 0);
  }
}

// defines what pins are being used, for data, clk, output pulse and output enable (active low)
Register::Register(int dataPin, int clkPin, int attOutputsPin, int outputOnPin){
  _validValues = true;
  _value = 0x00;
  _pinsMode = _4PINS;
  _triState = true;

  if (dataPin == clkPin || dataPin == attOutputsPin || dataPin == outputOnPin || clkPin == attOutputsPin ||
      clkPin == outputOnPin || attOutputsPin == outputOnPin){
    // set an 'error' value, due to the repeated values used
    _validValues = false;
    _pinsMode = _ERROR;
    setPins(-1, -1, -1, -1, -1);
  }

  else{
    // set the pins used, makes them output and starts them in the default value
    setPins(dataPin, clkPin, attOutputsPin, outputOnPin, -1);
    pinMode(dataPin, 1);
    pinMode(clkPin, 1);
    pinMode(attOutputsPin, 1);
    pinMode(outputOnPin, 1);
    digitalWrite(dataPin, 0);
    digitalWrite(clkPin, 0);
    digitalWrite(attOutputsPin, 0);
    digitalWrite(outputOnPin, 1);
  }
}

// defines what pins are being used, for data, clk, output pulse, output enable (active low) and reset pin (active low)
Register::Register(int dataPin, int clkPin, int attOutputsPin, int outputOnPin, int resetPin){
  _validValues = true;
  _value = 0x00;
  _pinsMode = _5PINS;
  _triState = true;
  
  if (dataPin == clkPin || dataPin == attOutputsPin || dataPin == outputOnPin || dataPin == resetPin ||
      clkPin == attOutputsPin || clkPin == outputOnPin || clkPin == resetPin || attOutputsPin == outputOnPin ||
      attOutputsPin == resetPin || outputOnPin == resetPin ){
    // set an 'error' value, due to the repeated values used
    _validValues = false;
    _pinsMode = _ERROR;
    setPins(-1, -1, -1, -1, -1);
  }

  else{
    // set the pins used, makes them output and starts them in the default value
    setPins(dataPin, clkPin, attOutputsPin, outputOnPin, resetPin);
    pinMode(dataPin, 1);
    pinMode(clkPin, 1);
    pinMode(attOutputsPin, 1);
    pinMode(outputOnPin, 1);
    pinMode(resetPin, 1);
    digitalWrite(dataPin, 0);
    digitalWrite(clkPin, 0);
    digitalWrite(attOutputsPin, 0);
    digitalWrite(outputOnPin, 1);
    digitalWrite(resetPin, 1);
  }
}

// this function is used to set to the microcontroler what pins are being used, its used when a new Register is created
void Register::setPins(int dataPin, int clkPin, int attOutputsPin, int outputOnPin, int resetPin){
  _dataPin = dataPin;
  _clkPin = clkPin;
  _attOutputsPin = attOutputsPin;
  _outputOnPin = outputOnPin;
  _resetPin = resetPin;
}

// this funcion atualizes the value of the register based on a value you pass to it
void Register::setAllOutputs(int value){
  if(_validValues){
    if (_value != value){
      _value = value;
      int state = 0;
      for(int i = 7; i >= 0; i--){
        state = value & (0x01 << i);
        digitalWrite(_dataPin, state);
        digitalWrite(_clkPin, 1);
        //delay(1);
        digitalWrite(_clkPin, 0);
        //delay(1);
      }
      digitalWrite(_attOutputsPin, 1);
      //delay(1);
      digitalWrite(_attOutputsPin, 0);
      //delay(1);

      if(_pinsMode > _3PINS)
        digitalWrite(_outputOnPin, 0);

      _triState = false;
    }
  }
}

// this funcion atualizes only one bit in a addr position of the register
void Register::setOneOutput(int _bit, int addr){
  if(_validValues){
    int tmp = _value & ~(0x01 << addr);
    tmp |= _bit << addr;
    setAllOutputs(tmp);
  }
}

// this funcion sets tri state on outputs (in case of using this pin) (actives low)
void Register::setTriState(bool triState){
  if((_pinsMode != _3PINS) && _validValues){
      digitalWrite(_outputOnPin, triState);
      _triState = true;
  }
}

// this functions resets the register ( if using 5 pins mode, do it on CI, not updating values again)
void Register::resetRegister(void){
  if (_pinsMode == _5PINS){
    digitalWrite(_outputOnPin, 0);
    //delay();
    digitalWrite(_outputOnPin, 1);
  }
  else{
    setAllOutputs(0x00);
  }
}

// this function returns the value in the register ( from 0 to 255 )
int Register::getValue(void){
  return _value;
}

// this function returns if a address of a register is in high or low state
bool Register::addrState(int addr){
  return _value & 0x01 << addr;
}

// this function returns an arduino pin used in the initialization of a register
int Register::getPin(int pin){
  switch(pin){
    case _DATA:
      return _dataPin;
    break;
    case _CLK:
      return _clkPin;
    break;
    case _ATT:
      return _attOutputsPin;
    break;
    case _OUT:
      return _outputOnPin;
    break;
    case _RST:
      return _resetPin;
      break;
  }
}

// this function returns what mode is actualy in use ( 3 pin mode, 4 pin mode or 5 pin mode )
int Register::getPinsMode(void){
  return _pinsMode;
}

// this function returns if the output is enabled or disabled
bool Register::getTriState(void){
  return _triState;
}