/*
 * Basic UARM servo controller node.
 * License: MIT
 * Author: Birkan Kolcu <birkan.kolcu@ozu.edu.tr>
 */
#include <ros.h>
#include <std_msgs/Int16.h>
#include <Servo.h>

#define BASE_SERVO_PIN 9          //PWM PIN
#define VERTICAL_SERVO_PIN 10     //PWM PIN
#define HORIZONTAL_SERVO_PIN 11   //PWM PIN
#define DEFAULT_BASE_POS 90
#define DEFAULT_VERTICAL_POS 90
#define DEFAULT_HORIZONTAL_POS 90

Servo baseServo;
Servo verticalServo;
Servo horizontalServo;

ros::NodeHandle  nh;

int preBase = DEFAULT_BASE_POS;
int preVertical = DEFAULT_VERTICAL_POS;
int preHorizontal = DEFAULT_HORIZONTAL_POS;

void baseCallback( const std_msgs::Int16& angle){
  int newPos = angle.data;
  if (preBase != newPos) {
    baseServo.write(newPos);
    preBase = newPos;
  }
}

void verticalCallback( const std_msgs::Int16& angle){
  int newPos = angle.data;
  if (preVertical != newPos) {
    verticalServo.write(newPos);
    preVertical = newPos;
  }
}

void horizontalCallback( const std_msgs::Int16& angle){
  int newPos = angle.data;
  if (preHorizontal != newPos) {
    horizontalServo.write(newPos);
    preHorizontal = newPos;
  }
}

ros::Subscriber<std_msgs::Int16> baseSub("base", baseCallback );
ros::Subscriber<std_msgs::Int16> verticalSub("vertical", verticalCallback );
ros::Subscriber<std_msgs::Int16> horizontalSub("horizontal", horizontalCallback );

void setup() {
  nh.initNode();
  nh.subscribe(baseSub);
  nh.subscribe(verticalSub);
  nh.subscribe(horizontalSub);

  baseServo.attach(BASE_SERVO_PIN);
  verticalServo.attach(VERTICAL_SERVO_PIN);
  horizontalServo.attach(HORIZONTAL_SERVO_PIN);

  baseServo.write(DEFAULT_BASE_POS);
  verticalServo.write(DEFAULT_VERTICAL_POS);
  horizontalServo.write(DEFAULT_HORIZONTAL_POS);
}

void loop() {
  nh.spinOnce();
  delay(1);
}
