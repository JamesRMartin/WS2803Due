#include "SPI.h"
#include <WS2803Due.h>
/*
*Title: IndividualLEDs
*Description:  Uses default constructor, and defines the necessary
*              information in the setup rather than at
*              instantiation.  Uses setLEDColor to address each
*              LED individually.
*More Info: Read the README
*/

//defining a default strip of WS2803 
WS2803Due strip = WS2803Due(); 
void setup(){
  Serial.begin(115200);
  strip.setNumLEDs(108);
  strip.setNumChips(6);
  strip.setClockDiv(3);
  strip.setExtLatching(true);
  strip.begin();
  strip.show();
}

void loop(){
  //cycles through each LED at full brightness
  //and 150 milisecond delay after each update
  for(byte j = 0; j <108; j++){
      strip.setLEDColor(j,255);
      strip.show();
      delayMicroseconds(400);//latching data
      strip.setLEDColor(j,0);
      delay(150);//Optional delay so that you can see
                  //what is happening.
    }
   //cycles through each LED at full brightness
  //and no delay, this is full speed 
  for(byte j = 0; j <108; j++){
      strip.setLEDColor(j,255);
      strip.show();
      delayMicroseconds(400);//latching data
      strip.setLEDColor(j,0);
    }
} 
     

