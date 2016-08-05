#include"ros/ros.h"
#include"keyboard/Key.h"
#include"std_msgs/Int16.h"

ros::NodeHandle nh;

ros::Publisher basePub;
ros::Publisher verticalPub;
ros::Publisher horizontalPub;

ros::Subscriber subKeyup;
ros::Subscriber subKeydown;

std_msgs::Int16 basePos;
std_msgs::Int16 verticalPos;
std_msgs::Int16 horizontalPos;

int publishRate;
int posIncreaseRate;

int baseMaxPosLimit;
int verticalMaxPosLimit;
int horizontalMaxPosLimit;

int baseMinPosLimit;
int verticalMinPosLimit;
int horizontalMinPosLimit;

int baseDefaultPos;
int verticalDefaultPos;
int horizontalDefaultPos;

ros::Timer baseTimer;
ros::Timer verticalTimer;
ros::Timer horizontalTimer;

bool isBaseIncrease;
bool isVerticalIncrease;
bool isHorizontalIncrease;

bool isBaseKeyDown = false;
bool isVerticalKeyDown = false;
bool isHorizontalKeyDown = false;

bool isBaseKeyInversed;
bool isVerticalKeyInversed;
bool isHorizontalKeyInversed;

void baseMove(const ros::TimerEvent&){
	if(isBaseIncrease){
		if(basePos.data<baseMaxPosLimit)
			basePos.data++;
		else
			basePos.data = baseMaxPosLimit;
	} else {
		if (basePos.data>baseMinPosLimit)
			basePos.data--;
		else
			basePos.data = baseMinPosLimit;
	}
}
void verticalMove(const ros::TimerEvent&){
	if(isVerticalIncrease){
		if(verticalPos.data<verticalMaxPosLimit)
                        verticalPos.data++;
                else
                        verticalPos.data = verticalMaxPosLimit;
        } else {
                if (verticalPos.data>verticalMinPosLimit)
                        verticalPos.data--;
                else
                        verticalPos.data = verticalMinPosLimit;
        }

}
void horizontalMove(const ros::TimerEvent&){
	if(isHorizontalIncrease){
		if(horizontalPos.data<horizontalMaxPosLimit)
				horizontalPos.data++;
		else
				horizontalPos.data = horizontalMaxPosLimit;
	} else {
		if (horizontalPos.data>horizontalMinPosLimit)
				horizontalPos.data--;
		else
				horizontalPos.data = horizontalMinPosLimit;
	}
}

bool isAnyValidKeyDown()
{
	return isBaseKeyDown || isVerticalKeyDown || isHorizontalKeyDown; 
}

void keyupMessageRecieved(const keyboard::Key& msg){
int keyCode = msg.code;
if (keyCode == msg.KEY_w || keyCode == msg.KEY_s) {
        verticalTimer.stop();
	isVerticalKeyDown = false;
}  else if (keyCode == msg.KEY_a || keyCode == msg.KEY_d){
       	baseTimer.stop();
	isBaseKeyDown = false;
} else if (keyCode == msg.KEY_e || keyCode == msg.KEY_q){
        horizontalTimer.stop();
	isHorizontalKeyDown = false;
} else if (keyCode == msg.KEY_r){
        basePos.data = baseDefaultPos;
        verticalPos.data = verticalDefaultPos;
        horizontalPos.data = horizontalDefaultPos;
		basePub.publish(basePos);
        verticalPub.publish(verticalPos);
        horizontalPub.publish(horizontalPos);
}
} 

void keydownMessageRecieved(const keyboard::Key& msg){
int keyCode = msg.code;
if (keyCode == msg.KEY_w) {
	isVerticalIncrease = !isVerticalKeyInversed;
	isVerticalKeyDown = true;
	verticalTimer.start();
} else if (keyCode == msg.KEY_s){
	isVerticalIncrease = isVerticalKeyInversed;
	isVerticalKeyDown = true;
	verticalTimer.start();
} else if (keyCode == msg.KEY_a){
	isBaseIncrease = !isBaseKeyInversed;
	isBaseKeyDown = true;
	baseTimer.start();
} else if (keyCode == msg.KEY_d){
	isBaseIncrease = isBaseKeyInversed;
	isBaseKeyDown = true;
	baseTimer.start();
} else if (keyCode == msg.KEY_e){
	isHorizontalIncrease = !isHorizontalKeyInversed;
	isHorizontalKeyDown = true;
	horizontalTimer.start();
} else if (keyCode == msg.KEY_q){
	isHorizontalIncrease = isHorizontalKeyInversed;
	isHorizontalKeyDown = true;
	horizontalTimer.start();
} 
}

void setParameters()
{
	ros::param::param<int>("~uarmPublishRate",publishRate,5);
	ros::param::param<int>("~uarmPoseRate",posIncreaseRate ,8);

	ros::param::param<bool>("~isBaseKeyInversed",isBaseKeyInversed ,"false");
	ros::param::param<bool>("~isVerticalKeyInversed",isVerticalKeyInversed ,"false");
	ros::param::param<bool>("~isHorizontalKeyInversed",isHorizontalKeyInversed ,"false");

	ros::param::param<int>("~baseMaxPosLimit",baseMaxPosLimit,180);
	ros::param::param<int>("~verticalMaxPosLimit",verticalMaxPosLimit ,180);
	ros::param::param<int>("~horizontalMaxPosLimit",horizontalMaxPosLimit,180);

	ros::param::param<int>("~baseMinPosLimit",baseMinPosLimit,0);
	ros::param::param<int>("~verticalMinPosLimit",verticalMinPosLimit,0);
	ros::param::param<int>("~horizontalMinPosLimit",horizontalMinPosLimit,0);

	ros::param::param<int>("~baseDefaultPos",baseDefaultPos,90);
	ros::param::param<int>("~verticalDefaultPos",verticalDefaultPos,90);
	ros::param::param<int>("~horizontalDefaultPos",horizontalDefaultPos,90);
}

void informUser()
{
	ROS_INFO_STREAM( "publishRate  " << publishRate );
	ROS_INFO_STREAM( "posIncreaseRate: " << posIncreaseRate );

	ROS_INFO_STREAM( "isBaseInversed  " << isBaseKeyInversed );
	ROS_INFO_STREAM( "isVerticalKeyInversed " << isVerticalKeyInversed );
	ROS_INFO_STREAM( "isHorizontalKeyInversed " << isHorizontalKeyInversed );

	ROS_INFO_STREAM( "baseMaxPosLimit  " << baseMaxPosLimit );
	ROS_INFO_STREAM( "verticalMaxPosLimit: " << verticalMaxPosLimit );
	ROS_INFO_STREAM( "horizontalMaxPosLimit " << horizontalMaxPosLimit );

	ROS_INFO_STREAM( "baseMinPosLimit  " << baseMinPosLimit );
	ROS_INFO_STREAM( "verticalMinPosLimit: " << verticalMinPosLimit );
	ROS_INFO_STREAM( "horizontalMinPosLimit " << horizontalMinPosLimit );

	ROS_INFO_STREAM( "baseDefaultPos  " << baseDefaultPos );
	ROS_INFO_STREAM( "verticalDefaultPos: " << verticalDefaultPos );
	ROS_INFO_STREAM( "horizontalDefaultPos " << horizontalDefaultPos );
}

void setTimers()
{
	baseTimer = nh.createTimer(ros::Duration(1/posIncreaseRate), &baseMove);
	baseTimer.stop();
	verticalTimer = nh.createTimer(ros::Duration(1/posIncreaseRate), &verticalMove);
	verticalTimer.stop();
	horizontalTimer = nh.createTimer(ros::Duration(1/posIncreaseRate),&horizontalMove);
	horizontalTimer.stop();
}

void setSubscribers()
{
	ros::Subscriber subKeydown = nh.subscribe("keydown", 1000, &keydownMessageRecieved);
	ros::Subscriber subKeyup = nh.subscribe("keyup", 1000, &keyupMessageRecieved);
}

void setPublishers()
{
	basePub = nh.advertise<std_msgs::Int16>("base",1000);
	verticalPub = nh.advertise<std_msgs::Int16>("vertical",1000);
	horizontalPub = nh.advertise<std_msgs::Int16>("horizontal",1000);
}

int main(int argc, char **argv){
ros::init(argc, argv, "uarm_basic_keyboard_controller_node");

setParameters();
setSubscribers();
setPublishers();
setTimers();

informUser();

ros::Rate loop_rate(publishRate);
while (ros::ok())
{
if (isAnyValidKeyDown()){
	basePub.publish(baseDefaultPos);
	verticalPub.publish(verticalDefaultPos);
	horizontalPub.publish(horizontalDefaultPos);	
}
ros::spinOnce();
loop_rate.sleep();
}
}
