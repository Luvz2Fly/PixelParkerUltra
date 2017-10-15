/*
 * Thanks for the code borrowed from:
 * http://randomnerdtutorials.com
 * http://playground.arduino.cc/Code/NewPing

Here is another installment of: "Solution in need of a Problem" Theater

The other day I realized I had a couple of Ultra Sonic Pingers, a basket of Arduinos,
4 hours of free time and a new dent on the hood of my car from hitting a shelf
in the garage while pulling in... that can mean only one thing, it was time to build
a digital ultrasonic NeoPixel parking assistant!

Meet the "Pixel Parker Ultra 4000!"
The code is ugly but it works and I will look for input on making this better...

Version 1.0 is simple...

16 NeoPixel Pixel ring inerfaces with 



WISH LIST:  LED Start Green FADE around the ring from:
 Green --> Yellow ---> Orange --> Red --> Flashing Red(ALL)



Comments HERE = Me "Thinking out loud"
 16 Pixels used to mesure distance from 200cm (~80 Inches) User Sets a STOP WARNING distance (apprx 10 inches from wall)
 So we must map apprx 80"--->~10"   1px ---->16px  Fade from GREEN (7px) TO YELLOW->Orange (5px) TO Red (Last 4px)
 For Testing purposes will set stopTarget = 10


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
int stopTarget = 10;  //Default alert inches after bootup


void setup() {
  pinMode(2,INPUT_PULLUP);

  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(50);
  delay(50);
}


void loop() {

   unsigned int median_time = sonar.ping_median(10);  // Get ping times averaged over (x) cycles
   unsigned int inch = sonar.convert_in(median_time); // convert times to inches

   int buttonVal = digitalRead(2);   //PULL UP Resister = Closed HIGH
   Serial.println(buttonVal);       // Looking for LOW to detect button push to ground
   if (buttonVal == LOW) {          // Upon push set current INCH to TARGET
       stopTarget = inch;
       Serial.println("Button Pressed");
       delay(250);
     }

   clearRing(); // MUST Clear every loop to
   distanceMeter(inch);    // pass current inches to meter function
}


//////// FUNCTION LIBRARY ////////////

void distanceMeter(int currentInches) {
// reminder to self:  curentInches = curent pinger value
int maxInches = 80;  // Ignore readings above 80 inches
int mapPixel = map(currentInches,maxInches,stopTarget, 0, 16);
// map the currentInches from pinger using max range to StopTarget ranger
// resulting value 0-15 represent the 16 pixels of the ring
Serial.print("Current Inches: "); Serial.println(currentInches);
Serial.print("Current Stop Target: "); Serial.println(stopTarget);
Serial.print("Turn on pixel: "); Serial.println(mapPixel);

if ((mapPixel > 0) && (mapPixel <= 10)) {  // 1 -> 10
  for(int i=0; i<mapPixel; i++) {
    strip.setPixelColor(i, 0, 255, 0);
  }
}

else if ((mapPixel >10) && (mapPixel <= 14)) { // 11 -> 14
  for(int i=0; i<mapPixel; i++) {
    strip.setPixelColor(i, 255, 165, 0);  //ORANGE
  }
}

else if (mapPixel == 15) {
  for(int i=0; i<mapPixel; i++) {
    strip.setPixelColor(i, 255, 0, 0);
  }
}

else if (mapPixel == 16) {
  redAlert();
}

else if ((mapPixel <= 0) || (mapPixel >= 17)) {   // Out of range/Invalid range
  for(int i=0; i<mapPixel; i++) {
    strip.setPixelColor(i, 0, 0, 255);
  }
}

strip.show();
//delay(500);
}



/////////////////////////////////////////////

void clearRing() {
  //Reset Ring
  for(int x = 0; x <17; x++) {
    strip.setPixelColor(x,0,0,0);
  }
  strip.show();
  }


////////////////////////////////////


void redAlert() {
    for(int x = 0; x <17; x++) {
      strip.setPixelColor(x,255,0,0);
  }

  strip.show();
  delay(250);
  clearRing();
}
