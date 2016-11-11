#include <ros/ros.h>
#include <std_msgs/String.h>

void gpioInit(){
	system("echo 26 > /sys/class/gpio/export");
	system("echo out > /sys/class/gpio/gpio26/direction");
	system("echo 0 > /sys/class/gpio/gpio26/value");

	system("echo 19 > /sys/class/gpio/export");
	system("echo out > /sys/class/gpio/gpio19/direction");
	system("echo 0 > /sys/class/gpio/gpio19/value");

	system("echo 13 > /sys/class/gpio/export");
	system("echo out > /sys/class/gpio/gpio13/direction");
	system("echo 0 > /sys/class/gpio/gpio13/value");

	system("echo 6 > /sys/class/gpio/export");
	system("echo out > /sys/class/gpio/gpio6/direction");
	system("echo 0 > /sys/class/gpio/gpio6/value");
}

void stop(){
	system("echo 0 > /sys/class/gpio/gpio26/value");
	system("echo 0 > /sys/class/gpio/gpio19/value");
	system("echo 0 > /sys/class/gpio/gpio13/value");
	system("echo 0 > /sys/class/gpio/gpio6/value");
}
void moveForward(){
	stop();
	system("echo 1 > /sys/class/gpio/gpio13/value");
	system("echo 1 > /sys/class/gpio/gpio6/value");
}
void moveBackward(){
	stop();
	system("echo 1 > /sys/class/gpio/gpio26/value");
	system("echo 1 > /sys/class/gpio/gpio19/value");
}
void moveRightward(){
	stop();
	system("echo 1 > /sys/class/gpio/gpio26/value");
	system("echo 1 > /sys/class/gpio/gpio6/value");
}

void moveLeftward(){
	stop();
	system("echo 1 > /sys/class/gpio/gpio19/value");
	system("echo 1 > /sys/class/gpio/gpio13/value");
}
//0: stop, 1:move forward, 2:move backward, 3:move rightward, 4:move leftward
void gpioControlMessageRecieved(const std_msgs::String::ConstPtr& msg){
	if (msg->data=="stop"){
		stop();
	} else if (msg->data=="move_forward"){
		moveForward();
	} else if (msg->data=="move_backward"){
		moveBackward();
	} else if (msg->data=="move_rightward"){
		moveRightward();
	} else if (msg->data=="move_leftward"){
		moveLeftward();
	}
}

int main(int argc, char **argv){
	gpioInit();
	ros::init(argc, argv, "test_gpio_control_node");
	ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe("test_gpio_control", 1000, &gpioControlMessageRecieved);
	ros::spin();
}

