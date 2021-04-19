/*
  This code was made by Ayslenon
  See the github repository on my repo
  This is a way to use 74HC595 on arduino with simple configuration and control of everything
     Example 01 - How to intialize a Register and set its output
  [x]Example 02 - How to change a single output
     Example 03 - How to use the Output Enable 74H595 pin
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
}

void loop() {
  registerTest.setAllOutputs(0b01011100);
  delay(1000);
  
  // from the past example, we will understand a new function
  // the setOneOutput using as parameter a address in the register [from 0 to 7]
  // we will set for example the bit 0 from the register to 1, then set manually all the 1 to 0
  // including the one that we just changed its value
  // and then the 4 most significative bits are going to be 1
  
  // in the position 0, we are putting a 1
  registerTest.setOneOutput(1,0);
  delay(100);

  // here we have the register like [01011101]
  
  // in the position 6, we are putting a 0
  registerTest.setOneOutput(0,6);
  delay(20);
  // here we have the register like [00011101]
  
  // in the position 4, we are putting a 0
  registerTest.setOneOutput(4,0);
  delay(20);
  // here we have the register like [00001101]
  
  // in the position 3, we are putting a 0
  registerTest.setOneOutput(3,0);
  delay(20);
  // here we have the register like [00000101]
  
  // in the position 2, we are putting a 0
  registerTest.setOneOutput(2,0);
  delay(20);
  // here we have the register like [00000001]
  
  // in the position 0, we are putting a 0
  registerTest.setOneOutput(0,0);
  delay(1000);
  // here we have the register like [00000000]
  
}
