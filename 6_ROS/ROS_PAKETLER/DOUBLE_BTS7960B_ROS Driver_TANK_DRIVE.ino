/*
 * Double BTS7960B ROS Driver for Tank-Drive Style Chasis.
 * License: MIT
 * Author: Birkan Kolcu <birkan.kolcu@ozu.edu.tr>
 */
 
#include <ros.h>
#include <std_msgs/Int16.h>
//#include <std_msgs/String.h>

//PIN 1 MOVE FORWARD
//PIN 2 MOVE BACKWARD

#define LEFT_MOTOR_PWM_PIN_1 6    //PWM
#define LEFT_MOTOR_PWM_PIN_2 9    //PWM
#define LEFT_MOTOR_ENABLE_PIN 7   //DIGITAL

#define RIGHT_MOTOR_PWM_PIN_1 10   //PWM
#define RIGHT_MOTOR_PWM_PIN_2 11   //PWM
#define RIGHT_MOTOR_ENABLE_PIN 8   //DIGITAL

int _pwmMagnitude = 255;

void stop(){
  analogWrite(LEFT_MOTOR_PWM_PIN_1,0);
  analogWrite(LEFT_MOTOR_PWM_PIN_2,0);
  analogWrite(RIGHT_MOTOR_PWM_PIN_1,0);
  analogWrite(RIGHT_MOTOR_PWM_PIN_2,0);
}

void moveForward(int pwmMagnitude){
  stop();
  analogWrite(LEFT_MOTOR_PWM_PIN_1, pwmMagnitude);
  analogWrite(RIGHT_MOTOR_PWM_PIN_1, pwmMagnitude);
}

void moveBackward(int pwmMagnitude){
  stop();
  analogWrite(LEFT_MOTOR_PWM_PIN_2, pwmMagnitude);
  analogWrite(RIGHT_MOTOR_PWM_PIN_2, pwmMagnitude);
}

void moveRightward(int pwmMagnitude){ //Left motor forward, Right motor backward
  stop();
  analogWrite(LEFT_MOTOR_PWM_PIN_1, pwmMagnitude);
  analogWrite(RIGHT_MOTOR_PWM_PIN_2, pwmMagnitude);
}

void moveLeftward(int pwmMagnitude){ //Left motor backward, Right motor forward
  stop();
  analogWrite(LEFT_MOTOR_PWM_PIN_2, pwmMagnitude);
  analogWrite(RIGHT_MOTOR_PWM_PIN_1, pwmMagnitude);
}

void directionCallback(const std_msgs::Int16& directionMessage){
  int movementState = directionMessage.data;
  if (movementState == 0){                     //move_forward
    moveForward(_pwmMagnitude);
  } else if (movementState == 1) {             //move_backward
    moveBackward(_pwmMagnitude);
  } else if (movementState == 2) {             //move_rightward
    moveRightward(_pwmMagnitude);
  } else if (movementState == 3) {             //move_leftward
    moveLeftward(_pwmMagnitude);
  } else if (movementState == 4) {             //stop
    stop();
  }
}

void pwmCallback(const std_msgs::Int16& pwmMessage){
  int pwmMagnitude = pwmMessage.data;
  if (pwmMagnitude > 255) {
    _pwmMagnitude = 255;
  } else if (pwmMagnitude < 0) {
    _pwmMagnitude = 0;
  } else {
    _pwmMagnitude = pwmMagnitude;
  }
}

void gpioInit(){
  pinMode(LEFT_MOTOR_PWM_PIN_1,OUTPUT);
  pinMode(LEFT_MOTOR_PWM_PIN_2,OUTPUT);
  pinMode(LEFT_MOTOR_ENABLE_PIN,OUTPUT);

  pinMode(RIGHT_MOTOR_PWM_PIN_1,OUTPUT);
  pinMode(RIGHT_MOTOR_PWM_PIN_2,OUTPUT);
  pinMode(RIGHT_MOTOR_ENABLE_PIN,OUTPUT);

  digitalWrite(LEFT_MOTOR_ENABLE_PIN,HIGH);
  digitalWrite(RIGHT_MOTOR_ENABLE_PIN,HIGH);
  stop();
}

ros::NodeHandle nh;
ros::Subscriber<std_msgs::Int16> directionSub("movement_state", directionCallback);
ros::Subscriber<std_msgs::Int16> pwmSub("pwmMagnitude", pwmCallback);


void setup() {
  gpioInit();
  nh.initNode();
  nh.subscribe(directionSub);
  nh.subscribe(pwmSub);
}

void loop() {
  nh.spinOnce();
  delay(1);
}
