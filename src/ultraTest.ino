/*
 * Posted on http://randomnerdtutorials.com
 * created by http://playground.arduino.cc/Code/NewPing
*/

#include <NewPing.h>
#include <Adafruit_NeoPixel.h>


#define PIN 6
#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 220
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB +
  NEO_KHZ800);

int setDist = 7;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
   Serial.begin(9600);
   strip.begin();
   strip.show(); // Initialize all pixels to 'off'
   strip.setBrightness(8);
}

void loop() {
   delay(50);
   unsigned int median_time = sonar.ping_median(5);  // Get ping times averaged over (x) cycles
   unsigned int inch = sonar.convert_in(median_time); // convert times to inches

   Serial.println(inch);  // DEBUG MODE - Show Inches

   /*if (inch < 7 && inch != 0)   // SIMULATE DISTANCe change
      {
        Serial.println("ALERT");
        Serial.println("=====");
      }
      */

      distanceMeter(inch);    // pass current inches to meter function


}

//////// FUNCTIONS ////////////

void distanceMeter(int currentInches) {
//Comments HERE = Me "Thinking out loud"
// 16 Pixels used to mesure distance from 200cm (~80 Inches)
// User Sets a STOP WARNING distance (apprx 10 inches from wall)
// So we must map apprx 80"--->~10"   1px ---->16px
// Fade from GREEN (7px) TO YELLOW->Orange (5px) TO Red (Last 4px)
// For Testing purposes will set stopTarget = 10

// curentInches = curent pinger value

int stopTarget = 10;  //Testing Variable - Normally set by button
int maxInches = 80;  // Going to ignore readings above 80 inches
int mapPixel = map(currentInches,maxInches,stopTarget, 1, 15);
// map the currentInches read from pinger using max range to StopTarget ranger
Serial.println(mapPixel);    //DEBUG PRINT MAPPED VALUE (What Pixel to light)
strip.setPixelColor(mapPixel, 0, 255, 0);
delay(300);
clearRing();
}

void clearRing() {
  //Reset Ring
  for(int x = 0; x <17; x++) {
    strip.setPixelColor(x,0,0,0);
  }
  strip.show();
  }
