#include <CapacitiveSensor.h>
#include "pitches.h"
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int shake = 40;
int base = 10;

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */

CapacitiveSensor   cs_4_2 = CapacitiveSensor(3,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired

const int buttonPin = 7;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup()                    
{
   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example

 /*
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
*/
   
   Serial.begin(9600);
   Serial.print("Setup\t");
   tone(8, NOTE_C4, 1000 / 4);
   delay(1.3 * 1000 / 4);
   noTone(8);

   // Servo
   myservo.attach(7);  // attaches the servo on pin 9 to the servo object
}

void loop()                    
{
    long start = millis();
    long total1 =  cs_4_2.capacitiveSensor(30);

    Serial.println(total1);                  // print sensor output 1
  
    delay(20);                             // arbitrary delay to limit data to serial port 
    
    if(total1>=200){
      Serial.print("wowowow");
      for (pos = base; pos <= shake+base; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);// waits 15ms for the servo to reach the position
      }

  
      delay(30);                       // waits 15ms for the servo to reach the position
   
      for (pos; pos >= base; pos -= 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);// waits 15ms for the servo to reach the position
      }
      delay(30);

    } 
  

}
