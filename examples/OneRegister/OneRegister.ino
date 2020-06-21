#include <EasyShiftout.h>

//**************************************************************//
//  Name    : OneRegister -> Single 74HC595 example             //
//  Author  : Tiago Rosolen                                     //
//  Date    : 2020                                              //
//  Version : 1.0                                               //
//  Notes   : Using a 74HC595 Shift Register with individual    //
//          : port writing                                      //
//****************************************************************

// Add the EasyShiftOut expansion
EasyShiftout expansion;

void setup() {

  Serial.begin(9600);

  /* Standart values:
  *  clockPin_ = 2 connected to SH_CP of 74HC595
  *  latchPin_ = 3 connected to ST_CP of 74HC595
  *  dataPin_  = 4 connected to DS of 74HC595
  *  Number of 74hc595 installed = 1
   */
  expansion.begin();
  
  Serial.println("----- INIT ------");
  
}
 
void loop() 
{

  for(int i=0; i < 8; i++)
  {
    expansion.writePort(i, HIGH);
    delay(1200);
  }
  for(int i=0; i < 8; i++)
  {
    expansion.writePort(i, LOW);
    delay(1200);
  }
  
}
