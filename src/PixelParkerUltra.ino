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

The code is ugly and dirty but it works - I would love input on making this better...

Version 1.0 is simple...

Interface a cheap ultrasonic ranger with a NeoPixel ring to be used as a distance meter

At bootup a defualt STOP target of 10 inches is set.  After that a momentary switch can
be used to lock in a new target (park your car where you want it and press button, the
new stop distace is set) MAGIC!

Meter/LED's first starts displaying based on the range variable (maxInches) which
can change to anything you want up to the pingers set maximum (#define MAX_DISTANCE)
in cm. (to convert break out the ol' slide rule, calculator or just ask Alexa (shhh!))

The 16 LED's on the ring 0 --> 15 are mapped from maxInches --> stopTarget to
create the correct Pixel meter scale (1 pixel on = first detection at maxInches up to
the last pixels (all on) coming on at stop target distance)

The Pixel count is then used to determine the pixel colors. I picked arbitary
(but logical points IMHO thank you) to swith ring from Green to Orange to Red to FLASHING

Build some 3D cases and mount on the wall!!

Option B - I thnk Amazon sells something like this for 10 bucks BUT thats not the point :)

==================================

WISH LIST (Mainly things taking advantage of NeoPixel's beauty!):
 LED Start of  Green FADE around the ring from:
  Green --> Yellow ---> Orange --> Red --> Flashing Red(ALL) -
  Nice Fading effects


Things to clean up:
 Change hard coded Pixel count of 16 to a variable to be used with other sizes or shapes (that was selfish of me)
 Fix mapping - I ended up with 17 pixels vs 16 (one of those silly '0' start thingys)

I TAKE NO RESPONSABILITY FOR ANY DAMAGE TO YOUR VEHICLE, HOME, PETS OR POWER TOOLS
WHILE USING THIS PARKING THING!  USE AT YOUR OWN RISK, SIDE EFECTS HAVE BEEN
REPORTED, CALL YOUR DOCOR IF YOU CANT PARK YOUR CAR FOR MORE THAN 4 HOURS!

Have Fun!

*/

#include <NewPing.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6
#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 220   // Set PINGER limits in cm (After this it will return 0 as distance)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB +
  NEO_KHZ800);

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int stopTarget = 10;  //Default alert inches after bootup


void setup() {
  pinMode(2,INPUT_PULLUP);

  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(50); // This thing is BLINDING at full so I preset what the max brightness is here in percentage
  delay(50); // Breathe..... it's go time!
}


void loop() {

   unsigned int median_time = sonar.ping_median(7);  // Get ping times averaged over (x) cycles
   unsigned int inch = sonar.convert_in(median_time); // convert average times to inches

   int buttonVal = digitalRead(2);   //internal PULL UP Resister => OFF = HIGH
   Serial.println(buttonVal);       // Looking for LOW to detect button pushed to ground
   if (buttonVal == LOW) {          // Upon push set current INCH to an ew STOP TARGET
       stopTarget = inch;
       Serial.println("Button Pressed");
       delay(250);
     }

   clearRing(); // MUST Clear every loop to create meter effect
   distanceMeter(inch);    // pass current inches to the meter function
}


//////// START FUNCTIONS ////////////

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
    strip.setPixelColor(i, 0, 0, 128);
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
