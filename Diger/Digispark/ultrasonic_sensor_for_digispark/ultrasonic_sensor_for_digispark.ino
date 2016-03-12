#define trigPin 2
#define echoPin 3
#include "DigiKeyboard.h"
void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
void loop() {
  int duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29;
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.println(distance);
  delay(500);
}
