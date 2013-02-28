/**
* Copyright (c)  2013 ICRL
*
* See the file LICENSE.txt for copying permission.
*
*
* File: WS2803Due.cpp
* Title: WS2803Due Class
* Author: James Martin
* Contact: vwgogreen@gmail.com
* Date: 02/24/2013
* Description: Open source library used to control RGB LED strips that are
*              driven by WS2803 LED driver chip(s).  Common methods are
*              implemented in order to easily set, update, and display 
*              user defined patterns.
* Detailed Information:  See the file README for detailed description,
*              implementation, system requirements, installation, method
*              definitions, and useful links.
*
**/

#include "SPI.h"
#include "WS2803Due.h"




/**
Default Constructor.  Calls to the setter methods after instantiating 
allow the environment to be set up later.  
totalChips, totalPixels, and clockDiv are set to 0. ExternalLatching is false.
@return: void
**/
WS2803Due::WS2803Due() {
	totalChips = 0;
	totalPixels = 0;
	clockDiv = 0;
	externalLatching = false;
}

/**
Constructor to be used when every port on the WS2803 chips are being
used.
@param: uint16_t numChips is the total number of WS2803's being used.
@param: uint8_t clock is the number of clock divisions to be used for
		the data rate transfer through SPI. 1 - 255
@param: bool latching defines wether the library will handle the the
		timing for latching the data, or it will be handled outside
		of the library. TRUE for external, FALSE for internal
@return: void
**/
WS2803Due::WS2803Due(uint16_t numChips, uint8_t clock, bool latching) {
	totalChips = numChips;
	totalPixels = totalChips*6;  //6 pixels per chip
	clockDiv = clock;
	externalLatching = latching;
}


/**
Constructor to be used when not every port on the WS2803 chips are being
used.  The number of pixels is also required.
@param: uint16_t numChips is the total number of WS2803's being used.
@param: uint16_t numPixels is the number of RGB LED's being used. If not
		using RGB LED's divide the total number of LED's by 3.
@param: uint8_t clock is the number of clock divisions to be used for
		the data rate transfer through SPI
@param: bool latching defines wether the library will handle the the
		timing for latching the data, or it will be handled outside
		of the library.
@return: void
**/
WS2803Due::WS2803Due(uint16_t numChips, uint16_t numPixels,  uint8_t clock, bool latching) {
	totalChips = numChips;
	totalPixels = numPixels;
	clockDiv = clock;
	externalLatching = latching;
}


/**
allocateMem() is called in order to allocate the proper amount of memory
to be used for storage later.  
@return: void
**/
void WS2803Due::allocateMem() {
	uint8_t ledcount = totalChips*18;
	totalLEDs = ((pixelData = (uint8_t *)calloc(ledcount, 1)) != NULL) ? ledcount : 0;
}


/**
begin() makes a call to allocateMem for data storage and starts the SPI.  If using 
the default constructor make sure to declare all other required variables before calling begin().
Otherwise, this only needs to be called once before being used.
@return: void
**/
void WS2803Due::begin(void) {
	allocateMem();

    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
    SPI.setClockDivider(clockDiv);
}


/**
show() takes all of the pixel data and sends it out through the SPI.  There is also a check
if external latching is being used to latch the data. 
@return: void
**/
void WS2803Due::show(void) {
	uint16_t i;
	for(i = 0; i < totalLEDs; i++){
		SPI.transfer(pixelData[i]);
	}

	if(!externalLatching){
		delay(1);
	}
}

/**
setLEDColor allows for the user to specify which individual LED and the brightness of that
LED.  This method is similar to other libraries.  Each pixel (e.g. SMD5050 RGB LED) has 3
individual LED diodes in them, one for Red, Green, and Blue.  Since the LED's are physical 
entities, they are 1 indexed instead of 0 indexed.  Because of the nature of the WS2803
and how they cascade data, and latch, the math converts the ledNum to the actual position
within the data stream where it will be stored.  This speeds up the transmition of data
once show() is called.
@param: uint16_t ledNum is the number of the led being set
@param: uint8_t brightness is the brightness of the led from 0-255
@return: void
**/

void WS2803Due::setLEDColor(uint16_t ledNum, uint8_t brightness) {

   uint8_t LEDOffset;
   uint16_t chipContainer;
   uint16_t ledNumPos;

   LEDOffset = ((ledNum-1)%18);
   chipContainer = ((ledNum-1)/18)+1;
   ledNumPos = (totalChips-chipContainer)*18+LEDOffset;


   uint8_t *storeLED = &pixelData[ledNumPos];
   *storeLED = brightness;
  
}

/**
setPixelColor allows for the user to specify which pixel they want to set, and then the
RGB values of that pixel.  Each pixel (e.g. SMD5050 RGB LED) has 3
individual LED diodes in them, one for Red, Green, and Blue.  Since the Pixels are physical 
entities, they are 1 indexed instead of 0 indexed.  Because of the nature of the WS2803
and how they cascade data, and latch, the math converts the pixelNum to the actual position
within the data stream where it will be stored.  This speeds up the transmition of data
once show() is called.
@param: uint16_t pixelNum is the number of the pixel being set
@param: uint8_t red is the brightness of the red led from 0-255
@param: uint8_t green is the brightness of the green led from 0-255
@param: uint8_t blue is the brightness of the blue led from 0-255
@return: void
**/
void WS2803Due::setPixelColor(uint16_t pixelNum, uint8_t red, uint8_t green, uint8_t blue) {
	 uint8_t pixelOffset;
	 uint16_t chipContainer;
	 uint16_t ledNum;

	 pixelOffset = ((pixelNum-1)%totalChips);
	 chipContainer = ((pixelNum-1)/totalChips)+1;
	 ledNum = (totalChips-chipContainer)*18+pixelOffset*3;
	 uint8_t *storeRed = &pixelData[ledNum];
     *storeRed = red;
	 uint8_t *storeGreen = &pixelData[ledNum+1];
     *storeGreen = green;
	 uint8_t *storeBlue = &pixelData[ledNum+2];
     *storeBlue = blue;
	 
}


//================================= Getters =================================
/**
getClockDiv returns the Clock Divider that was set for the SPI transmission.
@return: uint8_t clockDiv
**/
uint8_t WS2803Due::getClockDiv(void) {
	return clockDiv;
}

/**
getExtTime returns wether or not external latching is being used.
@return: bool externalLatching
**/
bool WS2803Due::getExtLatching(void) {
	return externalLatching;
}

/**
getNumChips returns the total number of WS2803 chips that were defined.
@return: uint16_t totalChips
**/
uint16_t WS2803Due::getNumChips(void) {
	return totalChips;
}

/**
getNumLEDs returns the total number of LEDs that were defined.
@return: uint16_t totalLEDs
**/
uint16_t WS2803Due::getNumLEDs(void) {
	return totalLEDs;
}

/**
getNumPixels returns the total number of pixels that were defined.
@return: uint16_t totalPixels
**/
uint16_t WS2803Due::getNumPixels(void) {
	return totalPixels;
}



//================================= Setters =================================

/**
setClockDiv sets the clock divider for the SPI
@param: uint8_t clock is used to set the clock divider, values from 1-255
@return: void
**/
void WS2803Due::setClockDiv(uint8_t clock) {
	clockDiv = clock;
}

/**
setExtLatching sets latching to be either internal by library or external by user
@param: bool latching TRUE for external and FALSE for internal
@return: void
**/
void WS2803Due::setExtLatching(bool latching) {
	externalLatching = latching;
}

/**
setNumChips sets the number of WS2803 chips being used
@param: uint16_t numChips is the total number of WS2803 chips being used
@return: void
**/
void WS2803Due::setNumChips(uint16_t numChips) {
	totalChips = numChips;
}

/**
setNumLEDs sets number of single LEDs being used
@return: void
**/
void WS2803Due::setNumLEDs(uint16_t numLEDs) {
	totalLEDs = numLEDs;
	totalPixels = numLEDs/3;
}

/**
setNumPixels sets number of pixels (e.g. SMD5050 RGB LEDS) being used
@return: void
**/
void WS2803Due::setNumPixels(uint16_t numPixels) {
	totalPixels = numPixels;
	totalLEDs = numPixels*3;
}