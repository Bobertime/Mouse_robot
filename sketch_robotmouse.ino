#include <NewPing.h>

#define TRIGGER_PINL  A1  // Arduino pin tied to trigger pin on ping sensor.
#define ECHO_PINL     A0  // Arduino pin tied to echo pin on ping sensor.

#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define TRIGGER_PINF  A2  // Arduino pin tied to trigger pin on ping sensor.
#define ECHO_PINF     A3  // Arduino pin tied to echo pin on ping sensor.

#define TRIGGER_PINR  A4  // Arduino pin tied to trigger pin on ping sensor.
#define ECHO_PINR     A5  // Arduino pin tied to echo pin on ping sensor.

NewPing sonarLeft(TRIGGER_PINL, ECHO_PINL, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonarRight(TRIGGER_PINR, ECHO_PINR, MAX_DISTANCE);
NewPing sonarFront(TRIGGER_PINF, ECHO_PINF, MAX_DISTANCE);

unsigned int pingSpeed = 30; // How frequently are we going to send out a ping (in milliseconds). 50ms would be 20 times a second.
unsigned long pingTimer; 

int m1p1 = 1 ;
int m1p2 = 2 ;

int m2p1 = 3 ;
int m2p2 = 4 ;

int enA = 5;
int enB = 6 ;

int baseSpeed = 60 ;

int borderWall = 10;
int straightWall = 4;

String durection = "FORWARD";

float lSensor, rSensor, fSensor;



void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.

  for (int i = 2; i <= 13; i++) //For Motor Shield
    pinMode(i, OUTPUT);



}

void loop() {
  ReadSensors();
  Move();
  Wall();
}



void ReadSensors() {
  lSensor = sonarLeft.ping_cm(); 
  rSensor = sonarRight.ping_cm(); 
  fSensor = sonarFront.ping_cm();
  Serial.print(" Left : ");
  Serial.print(lSensor);
  Serial.print(" cm ");
  Serial.print(" Right : ");
  Serial.print(rSensor);
  Serial.print(" cm ");
  Serial.print(" Front : ");
  Serial.print(fSensor);
  Serial.println(" cm ");
}

void Move() {
  if (durection == "FORWARD") {
    digitalWrite(m1p1, HIGH);
    digitalWrite(m1p2, LOW);

    digitalWrite(m2p1, HIGH);
    digitalWrite(m2p2, LOW);
    if (lSensor < straightWall) {
      analogWrite(enA, baseSpeed + 30);
      analogWrite(enB, baseSpeed);
    } else if (rSensor < straightWall) {
      analogWrite(enA, baseSpeed);
      analogWrite(enB, baseSpeed + 15);
    } else {
      analogWrite(enA, baseSpeed + 15);
      analogWrite(enB, baseSpeed);
    }
  } else if (durection == "LEFT") {
    digitalWrite(m1p1, HIGH);
    digitalWrite(m1p2, LOW);
    digitalWrite(m2p1, HIGH);
    digitalWrite(m2p2, LOW);
    analogWrite(enA, baseSpeed);
    analogWrite(enB, baseSpeed + 15);
  } else if (durection == "RIGHT") {
    digitalWrite(m1p1, HIGH);
    digitalWrite(m1p2, LOW);
    digitalWrite(m2p1, HIGH);
    digitalWrite(m2p2, LOW);
    analogWrite(enA, baseSpeed + 15);
    analogWrite(enB, baseSpeed);
  } else if (durection == "STOP") {
    digitalWrite(m1p1, LOW);
    digitalWrite(m1p2, LOW);
    digitalWrite(m2p1, LOW);
    digitalWrite(m2p2, LOW);
  }
}

void Wall() {
  if (fSensor > 10 && rSensor < 10 && lSensor < 10) {
    durection = "FORWARD";
  } else if (lSensor > 10) {
    durection = "LEFT";
  } else if (lSensor < 10 && fSensor < 10 && rSensor > 10) {
    durection == "RIGHT";
  } else if (lSensor < 10 && fSensor < 10 && rSensor < 10) {
    durection = "LEFT";
  }
}
