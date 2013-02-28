#include "SPI.h"
#include <WS2803Due.h>
/*
*Title: ColorFade
*Description:  Uses external latching and fills all pixels with
*              one color and starts from 0 brightness and then
*              goes up to the max of 255.  This example uses
*              external latching for better performance.
*              
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
  //Red fade
  for(byte i = 0; i < 255; i++){
    for(byte j = 1; j <= numPixels; j++){
      strip.setPixelColor(j, i, 0, 0);
    }
    strip.show();
    delayMicroseconds(400);//necessary for latching
    delay(10);//15 milisecond delay so that it you can see
              //see what is actually happening, can be removed
  }
  //Green fade
  for(byte i = 0; i < 255; i++){
    for(byte j = 1; j <= numPixels; j++){
      strip.setPixelColor(j, 0, i, 0);
    }
    strip.show();
    delayMicroseconds(400);//necessary for latching
    delay(10);//15 milisecond delay so that it you can see
              //see what is actually happening, can be removed
  }
  //Blue fade
  for(byte i = 0; i < 255; i++){
    for(byte j = 1; j <= numPixels; j++){
      strip.setPixelColor(j, 0, 0, i);
    }
    strip.show();
    delayMicroseconds(400);//necessary for latching
    delay(10);//15 milisecond delay so that it you can see
              //see what is actually happening, can be removed
  }
} 
     

