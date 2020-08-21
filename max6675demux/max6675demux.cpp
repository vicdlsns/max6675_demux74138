// this library is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple

#ifdef __AVR
  #include <avr/pgmspace.h>
#elif defined(ESP8266)
  #include <pgmspace.h>
#endif
#include <util/delay.h>
#include <stdlib.h>
#include "max6675demux.h"

MAX6675demux::MAX6675demux(int8_t SCLK, int8_t* DEMUX_PINS, int8_t EN, int8_t MISO, uint8_t ACTIVE_EN) {
  sclk = SCLK;
  en = EN;
  miso = MISO;
  demux_pins = DEMUX_PINS; //shallow copy
  len_demux_pins=sizeof(demux_pins)/sizeof(int8_t);
  active_en = ACTIVE_EN;
  inactive_en = !ACTIVE_EN;

  //define pin modes
  pinMode(en, OUTPUT);
  pinMode(sclk, OUTPUT); 
  pinMode(miso, INPUT);
  
  for (int i=0;i<len_demux_pins;i++)
  {
	  unsigned int pin=demux_pins[i];
	  pinMode(pin, OUTPUT); //set all pins to output
	  digitalWrite(pin, LOW); //set all pins to low
  }

  digitalWrite(en, inactive_en);
}

bool MAX6675demux::isValidIndex(int8_t index)
{
	return index>=2**len_demux_pins || index<0;
}

bool MAX6675demux::select(int8_t index)
{	
	if(isValidIndex(index)) //does not change selection if index is not valid
	{
		int8_t num = index;
		int8_t i = 0;

		while (num>0)
		{
			int8_t remainder=num%2;

			int8_t pin = demux_pins[i];
			digitalWrite(pin, remainder);

			num/=2;
			i++;
		}
		
		return true; //valid index
	}
	
	return false; //invalid index
}

double MAX6675demux::readCelsius(int8_t index) 
{
  if (select(index))
  {	  
	  uint16_t v;
	  
	  digitalWrite(en, active_en);
  	  _delay_ms(1);

	  v = spiread();
	  v <<= 8;
	  v |= spiread();

	  digitalWrite(en, inactive_en);

	  if (v & 0x4) {
	    // uh oh, no thermocouple attached!
	    return NAN; 
	    //return -100;
	  }

	  v >>= 3;

	  return v*0.25;
  }
	
  return NaN; //invalid index
  
}

double MAX6675demux::readFahrenheit(int8_t index) 
{
  return readCelsius(index) * 9.0/5.0 + 32;
}

byte MAX6675demux::spiread(void) 
{ 
  int i;
  byte d = 0;

  for (i=7; i>=0; i--)
  {
    digitalWrite(sclk, LOW);
    _delay_ms(1);
    if (digitalRead(miso)) {
      //set the bit to 0 no matter what
      d |= (1 << i);
    }

    digitalWrite(sclk, HIGH);
    _delay_ms(1);
  }

  return d;
}
