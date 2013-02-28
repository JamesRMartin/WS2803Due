#include "SPI.h"
#include "WS2803Due.h"

// Example to control WS2803Multiple-based RGB LED Modules in a strand or strip
// Written by Adafruit - MIT license
/*****************************************************************************/

//Constructor
WS2803Due::WS2803Due(uint16_t numChips, uint8_t clock, bool timing) {
  totalChips = numChips;
  totalPixels = totalChips*6;  //6 pixels per chip
  clockDiv = clock;

  allocateMem();
  if(timing){
	  externalTiming = true;
  }else{
	  externalTiming = false;
  }
}

WS2803Due::WS2803Due(uint16_t numChips, uint16_t numPixels,  uint8_t clock, bool timing) {
  totalChips = numChips;
  totalPixels = numPixels;
  clockDiv = clock;

  allocateMem();
  if(timing){
	  externalTiming = true;
  }else{
	  externalTiming = false;
  }
}

/*
WS2803Due::WS2803Due(unit16_t numChips, bool thread, uint8_t clock) {  //allows for external delay to use "threading" instead of delay
  totalChips = numChips;
  totalPixels = totalChips*6;  //6 pixels per chip
  clockDiv = clock;

  allocateMem();
  if(thread){
	  threading = true;
  }else{
	  threading = false;
  }
}

WS2803Due::WS2803Due(unit16_t numChips, uint16_t numPixels, bool thread, uint8_t clock) {  //allows for external delay to use "threading" instead of delay
  totalChips = numChips;
  totalPixels = numPixels;
  clockDiv = clock;

  allocateMem();
  if(thread){
	  threading = true;
  }else{
	  threading = false;
  }
}
*/

// Allocate 1 bytes per pixel, init to RGB 'off' state:
void WS2803Due::allocateMem() {
  /*uint8_t pixelCount = numPixels;
  uint16_t diffFromFull = 0;

	if( numPixels % 6 > 0){
          diffFromFull = 6 - (numPixels % 6);
   }
   
  //-- append the difference to the led count
  pixelCount = numPixels + diffFromFull;*/
  totalLEDs = ((pixels = (uint8_t *)calloc(totalChips*18, 1)) != NULL) ? totalChips*18 : 0;
}


// Starting SPI
void WS2803Due::begin(void) {
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
    //SPI.setClockDivider(SPI_CLOCK_DIV8);  // 2 MHz
    // WS2803Multiple datasheet recommends max SPI clock of 2 MHz, and 50 Ohm
    // resistors on SPI lines for impedance matching.  In practice and
    // at short distances, 2 MHz seemed to work reliably enough without
    // resistors, and 4 MHz was possible with a 220 Ohm resistor on the
    // SPI clock line only.  Your mileage may vary.  Experiment!

     SPI.setClockDivider(SPI_CLOCK_DIV6);  // 4 MHz
}



void WS2803Due::show(void) {
  uint8_t i, nl3 = numLEDs; // 1 bytes per LED

  //int tmpChips = (numLEDs / 18);

 /* for (int iChip = tmpChips-1 ; iChip >= 0 ; iChip--){
   // Write 8 bits per pixel:
   tmpOffset = (iChip*18);
	
     for(i=0; i<18; i++) {
		 SPI.transfer(pixels[tmpOffset + i]);
     }
  }*/

  for(i = 0; i < totalChips*18; i++){
	  SPI.transfer(pixels[i]);

  }

  if(!externalTiming){
	  delay(.5); // Latching data if it is to be handled by library.
  }
}

// Set brightness by individual LED, each pixel has a red, green, and blue LED inside them
void WS2803Due::setLEDColor(uint16_t ledNum, uint8_t brightness) {

   uint8_t *p = &pixels[ledNum];
    *p = brightness;
}


void WS2803Due::setPixelColor(uint16_t pixelNum, uint8_t red, uint8_t green, uint8_t blue) {
/*	uint8_t red = (ledColor >> 16) & 0xFF;
	uint8_t green = (ledColor >> 8) & 0xFF;
	uint8_t blue = ledColor & 0xFF;
	*/
	 uint8_t pixelOffset = pixelNum%totalChips-1;
	 uint16_t chipContainer = ((pixelNum-1)/totalChips)+1;
	 uint16_t ledNum = (totalChips-chipContainer)*18+pixelOffset;
	 uint8_t *p = &pixels[ledNum];
     *p = red;
	 uint8_t *p = &pixels[ledNum++];
     *p = green;
	 uint8_t *p = &pixels[ledNum++];
     *p = blue;
}

uint16_t WS2803Due::getNumPixels(void) {
  return totalPixels;
}

uint16_t WS2803Due::getNumLEDs(void) {
  return totalLEDs;
}

