#include<ros/ros.h>
#include<keyboard/Key.h>

#include<sstream>
#include<string.h>

std::string intToString(int number){
	std::ostringstream oss;
	oss << number;
	return oss.str();
}

void keyupMessageRecieved(const keyboard::Key& msg){
	ROS_INFO("%s",intToString(msg.code).c_str());
}
void keydownMessageRecieved(const keyboard::Key& msg){
	ROS_INFO("%s",intToString(msg.code).c_str());
}

int main(int argc, char **argv){
	ros::init(argc, argv, "little_mapper_teleop_node");
	ros::NodeHandle nh;
	ros::Subscriber sub_keydown = nh.subscribe("keyboard_node/keydown", 1000, &keyupMessageRecieved);
	ros::Subscriber sub_keyup = nh.subscribe("keyboard_node/keyup", 1000, &keydownMessageRecieved);
	ros::spin();
}
