/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

const int STATE_SWEEP = 0;
const int STATE_DATA = 1;

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int _LOW = 0;
int _HIGH = 150;

int SPEED = 15;
int inVal = 0;

int targetPos = 0;
int curPos = 0;

int _state = STATE_DATA;

void setup() {

  Serial.begin(9600);
  
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(curPos);
  delay(3000);
}

void loop() {

  //If we are reading data
  if (_state == STATE_DATA)
  {
  
    if (Serial.available()>0) 
    {      
      targetPos = map(Serial.parseInt(), 255, 0, _LOW, _HIGH);
    }

    if (targetPos > curPos) {
      curPos++;
    } else if (targetPos < curPos) {
      curPos--;
    }

    myservo.write(curPos);              // tell servo to go to position in variable 'pos'
    delay(SPEED);                       // waits 15ms for the servo to reach the position
  
  //IF WE ARE JUST SWEEPING THE SERVO
  } else {

    for (int pos = _LOW; pos <= _HIGH; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(SPEED);                       // waits 15ms for the servo to reach the position
    }
    for (int pos = _HIGH; pos >= _LOW; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(SPEED);                       // waits 15ms for the servo to reach the position
    }

    delay(3000);
  }
  
}

