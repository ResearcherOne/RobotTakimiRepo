#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>

ros::Publisher commandPublisher;

int move_forward_state_no;
int move_backward_state_no;
int move_rightward_state_no;
int move_leftward_state_no;
int stop_state_no;

void moveCommandReceived(const std_msgs::String::ConstPtr& msg){
    std_msgs::Int16 messageToSend;
    if (msg->data=="move_forward"){
        messageToSend.data = move_forward_state_no;
    } else if (msg->data=="move_backward"){
        messageToSend.data = move_backward_state_no;
    } else if (msg->data=="move_rightward"){
        messageToSend.data = move_rightward_state_no;
    } else if (msg->data=="move_leftward"){
        messageToSend.data = move_leftward_state_no;
    } else if (msg->data=="stop"){
        messageToSend.data = stop_state_no;
    }
    commandPublisher.publish(messageToSend);
}

//Default State Numbers 0:move forward, 1:move backward, 2:move rightward, 3:move leftward, 4: stop
void setParameters(){
    ros::param::param<int>("~move_forward_state_no",move_forward_state_no,0);
	ros::param::param<int>("~move_backward_state_no",move_backward_state_no ,1);
    ros::param::param<int>("~move_rightward_state_no",move_rightward_state_no,2);
	ros::param::param<int>("~move_leftward_state_no",move_leftward_state_no ,3);
    ros::param::param<int>("~stop_state_no",stop_state_no,4);
}

int main(int argc, char **argv){
    ros::init(argc, argv, "bts_driver_move_command_adapter_node");
    setParameters();

    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("move", 1000, &moveCommandReceived);
    commandPublisher = nh.advertise<std_msgs::Int16>("movement_state",1000);
    ros::spin();
}