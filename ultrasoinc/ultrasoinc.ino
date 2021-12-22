/*
   rosserial Ultrasound Example

   This example is for the Maxbotix Ultrasound rangers.
*/

#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>

ros::NodeHandle  nh;

sensor_msgs::Range range_msg1;
sensor_msgs::Range range_msg2;

ros::Publisher pub_range1( "/ultrasound_right", &range_msg1);
ros::Publisher pub_range2( "/ultrasound_front", &range_msg2);

const int adc_pin = 0;

int trigPin1 = 8;    // Trigger_1_right
int echoPin1 = 9;    // Echo_1_right
int trigPin2 = 10;    // Trigger_2_front 
int echoPin2 = 11;    // Echo_2_front
float duration, cm;


char frameid[] = "/ultrasound";



void setup()
{

  //Define inputs and outputs
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  nh.initNode();
  nh.advertise(pub_range1);
  nh.advertise(pub_range2);







  range_msg1.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg1.header.frame_id =  frameid;
  range_msg1.field_of_view = 0.1000;  // fake
  range_msg1.min_range = 0.0000;
  range_msg1.max_range = 1.5000;

  range_msg2.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg2.header.frame_id =  frameid;
  range_msg2.field_of_view = 0.1000;  // fake
  range_msg2.min_range = 0.0000;
  range_msg2.max_range = 1.5000;

}


long range_time;

void loop()
{


  range_msg1.range = readDistance(trigPin1, echoPin1);
  range_msg1.header.stamp = nh.now();
  pub_range1.publish(&range_msg1);


  range_msg2.range = readDistance(trigPin2, echoPin2);
  range_msg2.header.stamp = nh.now();
  pub_range2.publish(&range_msg2);
  nh.spinOnce();
}

int readDistance (byte ultra_trig, byte ultra_echo)
{
  digitalWrite(ultra_trig, LOW);
  delayMicroseconds(5);
  digitalWrite(ultra_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultra_trig, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(ultra_echo, INPUT);
  duration = pulseIn(ultra_echo, HIGH);

  // Convert the time into a distance
  cm = ((duration / 2) / 29.1);   //

  return cm ;

}




//int readDistance2 (byte ultra_trig, byte ultra_echo)
//{
// digitalWrite(trigPin2, LOW);
//  delayMicroseconds(5);
//  digitalWrite(trigPin2, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin2, LOW);
//
//  // Read the signal from the sensor: a HIGH pulse whose
//  // duration is the time (in microseconds) from the sending
//  // of the ping to the reception of its echo off of an object.
//  pinMode(echoPin2, INPUT);
//  duration = pulseIn(echoPin2, HIGH);
//
//  // Convert the time into a distance
//  cm = (duration/2) / 29.1;     //
//
//  return cm ;
//
//}


//// Convert the time into a distance
//  cm= (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
//  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
//
//  Serial.print(inches);
//  Serial.print("in, ");
//  Serial.print(cm);
//  Serial.print("cm");
//  Serial.println();
//
//  delay(250);
//}
