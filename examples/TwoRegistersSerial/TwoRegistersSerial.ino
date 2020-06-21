#include <EasyShiftout.h>

//**************************************************************//
//  Name    : EasyShiftOut -> Single 74HC595 example            //
//  Author  : Tiago Rosolen                                     //
//  Date    : 2020                                              //
//  Version : 1.0                                               //
//  Notes   : Using a 74HC595 Shift Register Serial Reading     //
//****************************************************************

// Add the EasyShiftOut expansion
EasyShiftout expansion;



/* How to use this Example:
 *  This example uses two 74hc595 expanders
 *  Open the Serial Monitor and write tue port and state that 
 *  you wish to execute.
 *  E.g.: 0=1 <send>
 *  The port 0 from first 595 goes to HIGH
 * 
 *  E.g.: 10=1 <send>
 *  The port 2 from second 595 goes to HIGH
 */
void setup() {

  Serial.begin(9600);

  /* Standart values:
  *  clockPin_ = 2 connected to SH_CP of 74HC595
  *  latchPin_ = 3 connected to ST_CP of 74HC595
  *  dataPin_  = 4 connected to DS of 74HC595
  *  Number of 74hc595 installed = 2
   */
  expansion.begin(2);
  
  Serial.println("----- INIT ------");
  
}
 
void loop() 
{
  if(Serial.available())
  {
    String req;
    while(Serial.available() > 0)
    {
      delay(1);
      req = Serial.readString(); 
    }
    String port = req.substring(0, req.indexOf('='));
    char value = req.charAt(req.indexOf('=')+1);

    int porti = atoi(port.c_str());
    bool valuei = (value == '1' ? true : false);
    expansion.writePort(porti, valuei);
  }
}
