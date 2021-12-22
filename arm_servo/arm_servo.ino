//#include "Arduino.h"
#include <ros.h>
#include <Servo.h>
#define SERVOPIN1 3
#define SERVOPIN2 4
#define RELAY 7



#include <std_msgs/Byte.h>
//ros::Publisher odom_pub1("physical_robot/arm", &odom_arm);

Servo myservo;  // create servo object to control a servo
Servo myservo_2;



byte y = 0;
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void handle_arm( const std_msgs::Byte& arm_msg) {
  byte y = arm_msg.data;
  if ( y == 1)
  {
    openArm();
  }
  else if (y == 2)
  {
    CloseArm();
  }

}


ros::NodeHandle  nh;
ros::Subscriber<std_msgs::Byte> sub("arm_commands", handle_arm);

void setup() {
  myservo.attach(SERVOPIN1);  // attaches the servo on pin 9 to the servo object
  myservo_2.attach(SERVOPIN2);
  pinMode(RELAY, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
  CloseArm();

  //Serial.begin(115200);
}
void loop() {
  nh.spinOnce();
  delay(1);

}

void openArm()
{
  for (pos = 0; pos <= 100; pos += 1)  // goes from 0 degrees to 180 degrees
  {
    // in steps of 1 degree
    myservo_2.write(pos);              // tell servo to go to position in variable 'pos'
    myservo.write(50 - pos / 2);
    delay(50);                       // waits 15 ms for the servo to reach the position

  }
  digitalWrite(7, 1);
}

void CloseArm()
{
  digitalWrite(7, 0);
  delay(40);
  for (pos = 100; pos >= 0; pos -= 1)  // goes from 0 degrees to 180 degrees
  {
    // in steps of 1 degree

    myservo_2.write(pos);              // tell servo to go to position in variable 'pos'
    myservo.write(50 - pos / 2);
    delay(30);                       // waits 15 ms for the servo to reach the position
  }
}
