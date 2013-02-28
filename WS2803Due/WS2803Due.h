/**
* Copyright (c)  2013 ICRL
*
* See the file LICENSE.txt for copying permission.
*
*
* File: WS2803.h
* Title: WS2803 Header
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

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

class WS2803Due {

 public:
  WS2803Due();
  WS2803Due(uint16_t numChips, uint8_t clock, bool latching);
  WS2803Due(uint16_t numChips, uint16_t numPixels,  uint8_t clock, bool latching);

  void
    begin(void),
	setClockDiv(uint8_t clock),
	setExtLatching(bool latching),
    setLEDColor(uint16_t ledNum, uint8_t ledBrightness),
	setNumChips(uint16_t numChips),
	setNumLEDs(uint16_t numLEDs),
	setNumPixels(uint16_t numPixels),
	setPixelColor(uint16_t numPixels, uint8_t red, uint8_t green, uint8_t blue),
	show(void);
	
  uint8_t
    getClockDiv(void);

  uint16_t
    getNumChips(void),
	getNumLEDs(void),
	getNumPixels(void);
	

  bool
    getExtLatching(void);


 private:
	
  uint16_t
    totalPixels,
	totalLEDs,
    totalChips;

  uint8_t
    clockDiv,
    *pixelData;

  void
    allocateMem(void);

  bool
    externalLatching;   
};
