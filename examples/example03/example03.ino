/*
  This code was made by Ayslenon
  See the github repository on my repo
  This is a way to use 74HC595 on arduino with simple configuration and control of everything
     Example 01 - How to intialize a Register and set its output
     Example 02 - How to change a single output
  [x]Example 03 - How to use the Output Enable 74H595 pin
     Example 04 - How to reset the register
     Example 05 - Descovering what the register is keeping
     Example 06 - Simple "digitalRead" to the register
     Example 07 - Descovering if the Output Enable is blocking the outputs
     Here for us, the 74HC595 pins are called this way:
  (sse datasheet: https://www.ti.com/lit/ds/symlink/cd74hc595.pdf)
    - pin 10 SRCLR' -> reset pin
    - pin 11 SRCLK  -> clk pin
    - pin 12 RCLK   -> attOutputs pin
    - pin 13 OE     -> outputOn pin (output enable)
    - pin 14 SER    -> data pin
  For all the tests we are going to use the following pins in arduino 
    - the set Pins function have as parameters, in this sequence:
    -- dataPin, clkPin, attOutputsPin, outputOnPin, resetPin
    - so we will use the pins from 3 to 7 on arduino, from dataPin to resetPin
    - note that you don't need use all the five pins, you can use just data, clk, attOutputs and outputOn
    - or even just data, clk and attOutputs
*/

#include <Register.h>
// here we set the registerTest using the pins 3, 4, 5, 6 and 7
Register registerTest(3, 4, 5, 6, 7);

void setup() {
  // the main function of a Register is set its output
  // let imagine that we have 8 bits, and we need to set the output in sequence 
  // from the 8th to the 1st position in that way: [01011100]
  // a simple way to do it is setting a binary value to the function setAllOutputs
  // or even a hexadecimal value, in this case it would be 0x5C
  // and if you want you can set too a decimal value, in this case: 92
  // we are going to use the binary-way
  registerTest.setAllOutputs(0b01011100);
  delay(1000);
  // this button will set the tri state
  pinMode(2, INPUT_PULLUP);

  bool triState = false;
  int buttonState;             // the current reading from the input pin
  int lastButtonState = LOW;   // the previous reading from the input pin
  
  // the following variables are unsigned longs because the time, measured in
  // milliseconds, will quickly become a bigger number than can be stored in an int.
  unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
  unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

}

void loop() {
  // we have already a register setted, so we will make a loop to change the tristate value
  // as long as we press the button, the tristate is high, otherwise is low


  // read the state of the switch into a local variable:
  int reading = digitalRead(2);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      triState = !reading;
      registerTest.setTriState(triState);
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
  }
