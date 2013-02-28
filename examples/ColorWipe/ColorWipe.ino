#include "SPI.h"
#include <WS2803Due.h>
/*
*Title: ColorWipe
*Description:  Uses external latching and fills each pixel
*              with a solid color until all are the same color
*              and then starts over with the next color.  Cycles
*              through RGB colors only.
*More Info: Read the README
*/

//defining a strip with 6 WS2803's, clock divider of 3, 
//external latching true
 WS2803Due strip = WS2803Due(6, 3, true);
 byte numPixels = strip.getNumPixels(); //number of pixels
void setup(){
  Serial.begin(115200);
  strip.begin();//initializing strip
  strip.show(); //clear mem

}


void loop(){
  //Red wipe
  for(byte j = 1; j <= numPixels; j++){
    strip.setPixelColor(j, 255, 0, 0);
    strip.show();
    delayMicroseconds(400);//necessary for latching
    delay(15);//15 milisecond delay so that it you can see
              //see what is actually happening can be removed
  }
  //Green wipe
  for(byte j = 1; j <= numPixels; j++){
    strip.setPixelColor(j, 0, 255, 0);
    strip.show();
    delayMicroseconds(400);//necessary for latching
    delay(15);//15 milisecond delay so that it you can see
              //see what is actually happening can be removed
  }
  //Blue wipe
  for(byte j = 1; j <= numPixels; j++){
    strip.setPixelColor(j, 0, 0, 255);
    strip.show();
    delayMicroseconds(400);//necessary for latching
    delay(15);//15 milisecond delay so that it you can see
              //see what is actually happening can be removed
  }
} 
     

