#include"ros/ros.h"
#include"keyboard/Key.h"
#include"std_msgs/Int16.h"

ros::Publisher basePub;
ros::Publisher verticalPub;
ros::Publisher horizontalPub;

ros::Subscriber subKeyup;
ros::Subscriber subKeydown;

std_msgs::Int16 basePos;
std_msgs::Int16 verticalPos;
std_msgs::Int16 horizontalPos;

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
		if(basePos.data<180)
			basePos.data++;
		else
			basePos.data = 180;
	} else {
		if (basePos.data>0)
			basePos.data--;
		else
			basePos.data = 0;
	}
}
void verticalMove(const ros::TimerEvent&){
	if(isVerticalIncrease){
		if(verticalPos.data<180)
                        verticalPos.data++;
                else
                        verticalPos.data = 180;
        } else {
                if (verticalPos.data>0)
                        verticalPos.data--;
                else
                        verticalPos.data = 0;
        }

}
void horizontalMove(const ros::TimerEvent&){
	if(isHorizontalIncrease){
                if(horizontalPos.data<180)
                        horizontalPos.data++;
                else
                        horizontalPos.data = 180;
        } else {
                if (horizontalPos.data>0)
                        horizontalPos.data--;
                else
                        horizontalPos.data = 0;
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
        basePos.data = 90;
        verticalPos.data = 90;
        horizontalPos.data = 90;
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

int main(int argc, char **argv){
ros::init(argc, argv, "uarm_basic_keyboard_controller_node");
ros::NodeHandle nh;

int publishRate;
int posIncreaseRate;

ros::param::param<int>("~uarmPublishRate",publishRate,5);
ros::param::param<int>("~uarmPoseRate",posIncreaseRate ,8);
ros::param::param<bool>("~isBaseKeyInversed",isBaseKeyInversed ,"false");
ros::param::param<bool>("~isVerticalKeyInversed",isVerticalKeyInversed ,"false");
ros::param::param<bool>("~isHorizontalKeyInversed",isHorizontalKeyInversed ,"false");
ROS_INFO_STREAM( "publishRate  " << publishRate );
ROS_INFO_STREAM( "posIncreaseRate: " << posIncreaseRate );
ROS_INFO_STREAM( "isBaseInversed  " << isBaseKeyInversed );
ROS_INFO_STREAM( "isVerticalKeyInversed " << isVerticalKeyInversed );
ROS_INFO_STREAM( "isHorizontalKeyInversed " << isHorizontalKeyInversed );


basePos.data = 90;
verticalPos.data = 90;
horizontalPos.data = 90;

ros::Subscriber subKeydown = nh.subscribe("keydown", 1000, &keydownMessageRecieved);
ros::Subscriber subKeyup = nh.subscribe("keyup", 1000, &keyupMessageRecieved);

basePub = nh.advertise<std_msgs::Int16>("base",1000);
verticalPub = nh.advertise<std_msgs::Int16>("vertical",1000);
horizontalPub = nh.advertise<std_msgs::Int16>("horizontal",1000);

baseTimer = nh.createTimer(ros::Duration(1/posIncreaseRate), &baseMove);
baseTimer.stop();
verticalTimer = nh.createTimer(ros::Duration(1/posIncreaseRate), &verticalMove);
verticalTimer.stop();
horizontalTimer = nh.createTimer(ros::Duration(1/posIncreaseRate),&horizontalMove);
horizontalTimer.stop();
ros::Rate loop_rate(publishRate);
while (ros::ok())
{
if (isAnyValidKeyDown()){
	basePub.publish(basePos);
	verticalPub.publish(verticalPos);
	horizontalPub.publish(horizontalPos);	
}
ros::spinOnce();
loop_rate.sleep();
}
}


