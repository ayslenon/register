// -------------------------------------------------------------------------------------
// Author: Ayslenon - 18/04/21
// Library to use (multiples) 74HC595 with Arduino easily
// - Resourses: 
// atualizes a register passing a valor to it
// atualizes just one position of a register
// resets a register
// capable of using more than one register
// tri-state output mode, when pin is enabled
// stores the value in register for an easy "digitalRead"
// check if a pin is high or low

// #define _DATA 1
// #define _CLK  2
// #define _ATT  3
// #define _OUT  4

// enum to identify pins
enum PINS : int{
  _DATA = 1,
  _CLK = 2,
  _ATT = 3,
  _OUT = 4,
  _RST = 5
};

// enum to identify the mode that is in use
enum PINMODE : int{
  _3PINS = 3,
  _4PINS = 4,
  _5PINS = 5,
  _ERROR = 0
};


class Register {
  private:
    int _value, _dataPin, _clkPin, _attOutputsPin, _outputOnPin, _resetPin, _pinsMode;
    bool _validValues, _triState;

    // this function is used to set to the microcontroler what pins are being used, its used when a new Register is created
    void setPins(int dataPin, int clkPin, int attOutputsPin, int outputOnPin, int resetPin);

  public:
    // defines what pins are being used, for data, clk and output pulse
    Register(int dataPin, int clkPin, int attOutputsPin);

    // defines what pins are being used, for data, clk, output pulse and output enable (active low)
    Register(int dataPin, int clkPin, int attOutputsPin, int outputOnPin);
    
    // defines what pins are being used, for data, clk, output pulse, output enable (active low) and reset pin (active low)
    Register(int dataPin, int clkPin, int attOutputsPin, int outputOnPin, int resetPin);
    
    // this funcion atualizes the value of the register based on a value you pass to it
    void setAllOutputs(int value);

    // this funcion atualizes only one bit in a addr position of the register
    void setOneOutput(int _bit, int addr);

    // this funcion sets output enable to high (in case of using this pin) (actives low)
    void setTriState(bool triState);

    // this functions resets the register ( if using 5 pins mode, do it on CI, not updating values again)
    void resetRegister(void);

    // this function returns the value in the register ( from 0 to 255 )
    int getValue(void);
    
    // this function returns if a address of a register is in high or low state
    bool addrState(int addr);

    // this function returns an arduino pin used in the initialization of a register
    int getPin(int pin);

    // this function returns what mode is actualy in use ( 3 pin mode, 4 pin mode or 5 pin mode )
    int getPinsMode(void);

    // this function returns if the output is enabled or disabled
    bool getTriState(void);
};
