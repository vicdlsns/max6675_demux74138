#include "max6675demux.h"

#define SCLK 13
#define EN 4
#define MISO 11
int8_t DEMUX_PINS[]={5,6,7};

MAX6675demux thermo = MAX6675demux(SCLK,DEMUX_PINS,EN,MISO);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  double temp[8];
  for (int i=0;i<8;i++)
  {
    temp[i]=thermo.readCelsius(i);
    Serial.print(F("thermo "));
    Serial.print(i);
    Serial.print(F(": "));
    Serial.print(temp[i]);
    Serial.print(F(" Celsius"));
    delay(125); // 125 ms  = 1000/8
  }
  
  delay(1000);

}
