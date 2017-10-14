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

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int stopTarget = 10;  //Testing Variable - Normally set by button


void setup() {
  pinMode(2,INPUT_PULLUP);

  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(50);
  delay(50);
}


void loop() {
   //delay(50);

   unsigned int median_time = sonar.ping_median(10);  // Get ping times averaged over (x) cycles
   unsigned int inch = sonar.convert_in(median_time); // convert times to inches

   int buttonVal = digitalRead(2);
   Serial.println(buttonVal);
   if (buttonVal == LOW) {
       stopTarget = inch;
       Serial.println("Button Pressed");
       delay(250);
     }

   clearRing(); // MUST Clear every loop to
   distanceMeter(inch);    // pass current inches to meter function
}


//////// FUNCTION LIBRARY ////////////

void distanceMeter(int currentInches) {
//Serial.println("distanceMeter:START");
//Comments HERE = Me "Thinking out loud"
// 16 Pixels used to mesure distance from 200cm (~80 Inches) User Sets a STOP WARNING distance (apprx 10 inches from wall)
// So we must map apprx 80"--->~10"   1px ---->16px  Fade from GREEN (7px) TO YELLOW->Orange (5px) TO Red (Last 4px)
// For Testing purposes will set stopTarget = 10
// curentInches = curent pinger value

int maxInches = 60;  // Ignore readings above 80 inches
int mapPixel = map(currentInches,maxInches,stopTarget, 0, 16);
// map the currentInches from pinger using max range to StopTarget ranger
// resulting value 0-15 represent the 16 pixels of the ring
Serial.print("Current Inches: "); Serial.println(currentInches);
Serial.print("Current Stop Target: "); Serial.println(stopTarget);
Serial.print("Turn on pixel: "); Serial.println(mapPixel);

if ((mapPixel >= 0) && (mapPixel <= 10)) {  // 1 -> 10
  for(int i=0; i<mapPixel; i++) {
    strip.setPixelColor(i, 0, 255, 0);
  }
}

else if ((mapPixel >10) && (mapPixel <= 14)) { // 11 -> 14
  for(int i=0; i<mapPixel; i++) {
    strip.setPixelColor(i, 255, 165, 0);  //ORANGE
  }
}

else if (mapPixel > 14) {
  for(int i=0; i<mapPixel; i++) {
    strip.setPixelColor(i, 255, 0, 0);
  }
}

//else {}

strip.show();
//delay(500);
}


void clearRing() {
  //Reset Ring
  for(int x = 0; x <17; x++) {
    strip.setPixelColor(x,0,0,0);
  }
  strip.show();
  }
