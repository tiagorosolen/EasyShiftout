/*
	Please fine Licensing and Usage information in header file
*/

#include "EasyShiftout.h"

#define BIT_ISSET(var, pos) (!!((var) & (1ULL<<(pos))))


// All default values
void EasyShiftout::begin()
{
	begin(latchPin_, clockPin_, dataPin_, c595Count_);
}

// Default pins but custom chip count
void EasyShiftout::begin(char cis_p)
{
	begin(latchPin_, clockPin_, dataPin_, cis_p);
}

// fully customized
void EasyShiftout::begin(char latchPin_p, char clockPin_p, char dataPin_p, char cis_p)
{
	pinMode(latchPin_p, OUTPUT);
	pinMode(clockPin_p, OUTPUT);
	pinMode(dataPin_p, OUTPUT);
	latchPin_ = latchPin_p;
	clockPin_ = clockPin_p;
	dataPin_ = dataPin_p;
	c595Count_ = cis_p;

	lastValidIndex = (c595Count_ * 8) -1;

	// Write 0 in all ports
	for(int i=0; i < c595Count_; i++)
	{
		registers[i] = 0;
	}
	shiftRegister();
}

/*  Updates a single bit of the register and  */
void EasyShiftout::writePort(unsigned char port, bool value, bool shift /* = true */)
{
	if(port <= lastValidIndex)
	{
		int index = (port == 0 ? 0 : port / 8);
		int pin = (int) (port - (index * 8));

		if(value)
		{
			SET_BIT(index, pin);
		}
		else
		{
			CLEAR_BIT(index, pin);	
		}

		if(shift)
		{
			shiftRegister();
		}
	}
	// else: invalid port, just ignore it
}


/*  Updates a whole register of the 595  */
void EasyShiftout::writeRegister(unsigned char registerNum, byte value, bool shift /* = true */)
{
	if(registerNum <= (c595Count_ -1))
	{
		registers[registerNum] = value;
	}
	
	if(shift)
	{
		shiftRegister();
	}
}


/* ------- Reading Methods ------- */

// Returns the current state of the port
bool EasyShiftout::readPort(unsigned char port)
{
	bool ret = false;
	if(port <= lastValidIndex)
	{
		int index = port / 8;
		int pin = (int) (port - (index * 8));
		
		if(BIT_ISSET(registers[index], pin) ?  ret = true : ret = false);
	}
	return ret;
}

// Returns the current state of the register
byte EasyShiftout::readRegister(unsigned char r)
{
	if(r <= (c595Count_ -1))	
	{
		return registers[r];
	}
	else
	{
		return 0;
	}
}

// Send registers to shiftout()
void EasyShiftout::flush()
{
	shiftRegister();
}

// Private

void EasyShiftout::shiftRegister()
{
	int pinState;

	//Latch - Hold LOW for entire transmission 
	digitalWrite(latchPin_, LOW);  // D3
	digitalWrite(clockPin_, 0);    // D4
	digitalWrite(dataPin_, 0);     // 

	// Run the shift once for every 595
	for(int j = 0; j < c595Count_; j++)
	{
	  	// The values are shifted backwards
	  	// The First 595 (connected to uC) must be the last one
		for (int i = 7; i >= 0; i--)  {
			digitalWrite(clockPin_, 0);
			if ( registers[c595Count_ -j -1] & (1<<i) ) {
				pinState = 1;
			}
			else {  
				pinState = 0;
			}
			digitalWrite(dataPin_, pinState);
			digitalWrite(clockPin_, 1);
			digitalWrite(dataPin_, 0);
		}
	}
  
  
  // Latch - Hold LOW for entire transmission 
  digitalWrite(latchPin_, HIGH);
}

void EasyShiftout::SET_BIT(byte indexi, char bit)
{
	registers[indexi] |= 1 << bit;	
}

void EasyShiftout::CLEAR_BIT(byte indexi, char bit)
{
	registers[indexi] &= ~(1 << bit);
}
