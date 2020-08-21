# max6675_demux74138

This Arduino lib was made in order to use more than one MAX6675-based Thermocouple in combination with a 74138 Demultiplexer IC, allowing up to 8 thermocouples to be read with less than 8 selection pins.

# Connections
    -All Thermocouple SCLK pins are connected to the same Arduino SPI clock pin;
    -All Thermocouple SO pins are connected to the same Arduino SPI MISO pin;
    -Each Thermocouple CS pin is connected to a different output of the 74138 Demux (¬O0 to ¬O7);
    -Each Demux selector pin (A0, A1 and A2) is connected to a different digital pin on Arduino;
    -Only one of the Demux enable pins (¬E1, ¬E2 or E3) is connected to a digital pin on Arduino; 
    -The other enable pins are connected to Vcc or GND, corresponding to its active state (Active high = Vcc, Active low = GND).

# Functions:
    MAX6675demux(int8_t SCLK, int8_t* DEMUX_PINS, int8_t EN, int8_t MISO, uint8_t ACTIVE_EN=LOW)
        -Constructor function;
        -SCLK: SPI clock pin;
        -DEMUX_PINS: Demux selector pins. The "0" index of the array (first element) corresponds to A0 pin, "1" to A1, and "2" to A2;
        -EN: Demux enable pin;
        -MISO: SPI Slave Out pin;
        -ACTIVE_EN: State in which the EN pin is set to be active.
        
    double readCelsius(int8_t index)
        -Returns the temperature in Celsius format;
        -index: Number of the demux output pin in which the wanted termocouple CS is connected.
        
    double readFahrenheit(int8_t index)
        -Returns the temperature in Fahrenheit format;
        -index: Number of the demux output pin in which the wanted termocouple CS is connected.
        
    double readFarenheit(int8_t index)
        -Same as readFahrenheit(int8_t index).

