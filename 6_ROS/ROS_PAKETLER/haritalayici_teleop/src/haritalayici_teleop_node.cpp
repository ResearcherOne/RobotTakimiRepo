#include"ros/ros.h"
#include"keyboard/Key.h"

#include<sstream>
#include"std_msgs/String.h"

ros::Publisher chatter_pub;

void keyupMessageRecieved(const keyboard::Key& msg){
ROS_INFO("%d",msg.code);

std_msgs::String message;
std::stringstream ss;
ss << "stop";

chatter_pub.publish(message);
}


void keydownMessageRecieved(const keyboard::Key& msg){
std_msgs::String message;
std::stringstream ss;

int keyCode = msg.code;
if (keyCode = 274) {
	ss << "274 basildi";
} else {
	ss << "NOOOOO";
}
chatter_pub.publish(message);
}

int main(int argc, char **argv){
ros::init(argc, argv, "little_mapper_teleop_node");
ros::NodeHandle nh;
ros::Subscriber sub_keydown = nh.subscribe("keydown", 1000, &keyupMessageRecieved);
ros::Subscriber sub_keyup = nh.subscribe("keyup", 1000, &keydownMessageRecieved);
chatter_pub = nh.advertise<std_msgs::String>("move",1000);
ros::spin();
}
