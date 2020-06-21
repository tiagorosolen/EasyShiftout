/*
  ****************************************************************************
  
  EasyShiftout.h


  This library expands the use of shiftout() by allowing easy manipulation
  of individual values of the shift register.

  Please check the oficial Arduino shifout() documentation for more 
  information on how to connect your 74HC595.

  This library is free software, please consider make your 
  work accessible to others too!
  
  * Author: Tiago Rosolen (2020)
  * License: MIT "ultra permissive" License (license file in same folder)
  * http://theprotoblog.com
  ****************************************************************************
*/

#ifndef EASYSHIFTOUT_h
#define EASYSHIFTOUT_h

#include "arduino.h"

class EasyShiftout
{
private:
  int registers[16];
public:
  EasyShiftout(){}
  void begin();
  void begin(char cis_p);
  void begin(char latchPin_p, char clockPin_p, char dataPin_p, char cis_p);


  /* ------- Writing Methods ------- */

  /*  Updates a single bit of the register  */
  void writePort(unsigned char port, bool value, bool shift = true);

  /*  Updates a whole register of the 595  */
  void writeRegister(unsigned char registerNum, byte value, bool shift = true);

  /* ------- Reading Methods ------- */

  // Returns the current state of the port
  bool readPort(unsigned char port);

  // Returns the current state of the register
  byte readRegister(unsigned char registerNum);

  // Send registers to shiftout()
  void flush();

private:
  void shiftRegister();

  void SET_BIT(byte myByte, char bit);
  void CLEAR_BIT(byte myByte, char bit);

  //Pin connected to SH_CP of 74HC595
  char clockPin_  = 2;
  //Pin connected to ST_CP of 74HC595
  char latchPin_ = 3;
  //Pin connected to DS of 74HC595
  char dataPin_ = 4;

  // Number of connected 595s
  char c595Count_ = 1;

  char lastValidIndex = 0;

};

#endif