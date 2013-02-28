#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

class WS2803Due {

 public:
  WS2803Due(uint16_t numChips, uint8_t clock, bool timing); // SPI only
  WS2803DueWS2803Due(uint16_t numChips, uint16_t numPixels,  uint8_t clock, bool timing) // SPI only
  //WS2803Due(unit16_t numChips, bool thread, uint8_t clockDiv); //SPI without the delay built in.
  //WS2803Due(void); // Empty constructor
  void
    begin(void),
    show(void),
    setPixelColor(uint16_t ledNum, uint8_t ledBrightness),
	setPixelColor(uint16_t pixelNum, uint8_t red, uint8_t green, uint8_t blue);

  uint8_t *p;

 private:
	int totalChips;
	int tmpOffset;
	
  uint16_t
    totalPixels,
	totalLEDs;
  uint8_t
    clockDiv,
    *pixels; // Holds color values for each LED (3 bytes each)
  void
    allocateMem();
  boolean
    externalTiming;   
};
