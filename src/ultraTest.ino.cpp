# 1 "c:\\users\\gary\\appdata\\local\\temp\\tmprbijxy"
#include <Arduino.h>
# 1 "C:/Users/Gary/Documents/Git/parkingtemp/PixelParkerUltra/src/ultraTest.ino"
# 1 "C:/Users/Gary/Documents/Git/parkingtemp/PixelParkerUltra/src/RngTest.ino"
#include <Adafruit_NeoPixel.h>



#define PIN 6
# 23 "C:/Users/Gary/Documents/Git/parkingtemp/PixelParkerUltra/src/RngTest.ino"
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);
void setup();
void loop();
void distanceMeter(int currentInches);
void colorWipe(uint32_t c, uint8_t wait);
void rainbow(uint8_t wait);
void rainbowCycle(uint8_t wait);
uint32_t Wheel(byte WheelPos);
#line 31 "C:/Users/Gary/Documents/Git/parkingtemp/PixelParkerUltra/src/ultraTest.ino"
void setup() {





  Serial.begin(9600);







  strip.begin();

  strip.show();

  strip.setBrightness(8);



}



void loop() {
# 75 "C:/Users/Gary/Documents/Git/parkingtemp/PixelParkerUltra/src/RngTest.ino"
for(int x = 79; x >0; x--) {

  Serial.println(x);

  distanceMeter(x);

  delay(250);

}



Serial.println("---------");

}



void distanceMeter(int currentInches) {
# 113 "C:/Users/Gary/Documents/Git/parkingtemp/PixelParkerUltra/src/RngTest.ino"
int stopTarget = 10;

int maxInches = 80;

int mapPixel = map(currentInches,maxInches,stopTarget, 1, 15);



Serial.println(mapPixel);



delay(200);



}
# 141 "C:/Users/Gary/Documents/Git/parkingtemp/PixelParkerUltra/src/RngTest.ino"
void colorWipe(uint32_t c, uint8_t wait) {

  for(uint16_t i=0; i<strip.numPixels(); i++) {

      strip.setPixelColor(i, c);

      strip.show();

      delay(wait);

  }

}



void rainbow(uint8_t wait) {

  uint16_t i, j;



  for(j=0; j<256; j++) {

    for(i=0; i<strip.numPixels(); i++) {

      strip.setPixelColor(i, Wheel((i+j) & 255));

    }

    strip.show();

    delay(wait);

  }

}





void rainbowCycle(uint8_t wait) {

  uint16_t i, j;



  for(j=0; j<256*5; j++) {

    for(i=0; i< strip.numPixels(); i++) {

      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));

    }

    strip.show();

    delay(wait);

  }

}







uint32_t Wheel(byte WheelPos) {

  if(WheelPos < 85) {

   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);

  } else if(WheelPos < 170) {

   WheelPos -= 85;

   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);

  } else {

   WheelPos -= 170;

   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);

  }

}