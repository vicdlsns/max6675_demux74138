// this library is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class MAX6675demux {
 public:
  MAX6675demux(int8_t SCLK, int8_t* DEMUX_PINS, int8_t EN, int8_t MISO, uint8_t ACTIVE_EN=LOW);

  double readCelsius(int8_t index);
  double readFahrenheit(int8_t index);
  // For compatibility with older versions:
  double readFarenheit(int8_t index) { return readFahrenheit(index); };
 private:
  int8_t sclk, miso, en;
  int8_t* demux_pins;
  uint8_t active_en, inactive_en;
  
  
  uint8_t spiread(void);
  
  void select(int8_t index);
};
