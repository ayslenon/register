/*
  This code was made by Ayslenon
  See the github repository on my repo
  This is a way to use 74HC595 on arduino with simple configuration and control of everything
     Example 01 - How to intialize a Register and set its output
     Example 02 - How to change a single output
     Example 03 - How to use the Output Enable 74H595 pin
     Example 04 - How to reset the register
     Example 05 - Descovering what the register is keeping
     Example 06 - Simple "digitalRead" to the register
  [x]Example 07 - Descovering if the Output Enable is blocking the outputs
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
  // for this example, we will set the output enable after the dalay to see the outputs going to tristate
  // and in the loop we will see the tristate and change it to see again the outputs as we set 
  registerTest.setTriState(true);
  delay(1000);
  Serial.begin(9600);
  int counter = 1;
  bool triState = false;
  bool triStateFromFunction = false;
}

void loop() {
  // if the counter is a pair number, triState will invert, so for every 200 ms, we should see the outputs changing
  // from triState and normal state
  // and for every 100 ms, we will see in the Serial monitor the triState value using a function designed to it
  
  if ((counter % 2) == 0){
    registerTest.setTriState(triState);
    triState = !triState;
  }
  triStateFromFunction = registerTest.getTriState();
  Serial.print("The tristate is: ");
  Serial.println(triStateFromFunction);
  delay(100);
  counter++;
}
