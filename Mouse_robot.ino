/*********** MOTOR PINS *********/
const byte m1p1 = 2;  // Left Motor Negative
const byte m1p2 = 3;  // Left Motor Positive

const byte m2p1 = 4;  // Right Motor Negative
const byte m2p2 = 5;  // Right Motor Positive

const byte ENA = 9;  // Enable for Left motor
const byte ENB = 10;  // Enable for Right motor

int speed = 80; 

/*********** Ultrasonic sensor *********/
const int TrigR = A0;
const int EchoR = A1;

const int TrigF = A3;
const int EchoF = A2;

const int TrigL = A5;
const int EchoL = A4;

float durationLeft,durationForward,durationRight,distanceLeft,distanceForward,distanceRight;


void setup() {
  // Motor 
  pinMode(m1p1, OUTPUT);
  pinMode(m1p2, OUTPUT);
  pinMode(m2p1, OUTPUT);
  pinMode(m2p2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  // Ultrasonic
  pinMode(TrigR, OUTPUT);
  pinMode(EchoR, INPUT);
  pinMode(TrigF, OUTPUT);
  pinMode(EchoF, INPUT);
  pinMode(TrigL, OUTPUT);
  pinMode(EchoL, INPUT);
  Serial.begin(9600);
}

void loop() {
  serialDistanceForward();
  serialDistanceLeft();
  serialDistanceRight();
  if (distanceForward <= 10) {
    moveBehind();
  } else {
    moveForward();
  }
}

void stopAll() {
  digitalWrite(m1p1, LOW);
  digitalWrite(m1p2, LOW);

  digitalWrite(m2p1, LOW);
  digitalWrite(m2p2, LOW);
  delay(500);
}

void moveForward() {
  delay(50);
  analogWrite(ENA, speed);
  analogWrite(ENB, speed); 

  digitalWrite(m1p1, HIGH);
  digitalWrite(m1p2, LOW);

  digitalWrite(m2p1, HIGH);
  digitalWrite(m2p2, LOW);
}

void moveBehind() {
  delay(50);
  analogWrite(ENA, speed);
  analogWrite(ENB, speed); 

  digitalWrite(m1p1, HIGH);
  digitalWrite(m1p2, LOW);

  digitalWrite(m2p1, LOW);
  digitalWrite(m2p2, HIGH);
}

float serialDistanceForward () {
  digitalWrite(TrigF, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigF, HIGH);
  delayMicroseconds(2);
  digitalWrite(TrigF, LOW);

  durationForward = pulseIn(EchoF, HIGH);
  distanceForward = (durationForward*.0343)/2;
  Serial.print("Distance: ");
  return distanceForward;
}

float serialDistanceLeft () {
  digitalWrite(TrigL, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigL, HIGH);
  delayMicroseconds(2);
  digitalWrite(TrigL, LOW);

  durationLeft = pulseIn(EchoL, HIGH);
  distanceLeft = (durationLeft*.0343)/2;
  return distanceLeft;
}

float serialDistanceRight () {
  digitalWrite(TrigR, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigR, HIGH);
  delayMicroseconds(2);
  digitalWrite(TrigR, LOW);

  durationRight = pulseIn(EchoR, HIGH);
  distanceRight = (durationRight*.0343)/2;
  return distanceRight;
}
