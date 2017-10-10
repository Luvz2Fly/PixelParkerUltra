/*
 * Posted on http://randomnerdtutorials.com
 * created by http://playground.arduino.cc/Code/NewPing
*/

#include <NewPing.h>

#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 200

int setDist = 7;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
   Serial.begin(9600);
}

void loop() {
   delay(50);
   unsigned int median_time = sonar.ping_median(5);
   unsigned int inch = sonar.convert_in(median_time);
   Serial.println(inch);
   if (inch < 7 && inch != 0)
      {
        Serial.println("ALERT");
        Serial.println("=====");
      }

}
