// Created by Zachary Metcalf
// zachmetcalf@gmail.com
//
// Wiimote.cpp
// TCPLibrary
//
// Main for Wiimote
//

#include <TCPLibrary.h>

// ROS Includes
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/Joy.h>

// ROS Subscriber
ros::Subscriber subscriber;

// Global Wiimote Data
unsigned int curWiimoteState;
unsigned int prevWiimoteState;

// Global TCPCLient
TCPLibrary::Client* client;
 
void WiimoteCallBack(const sensor_msgs::Joy::ConstPtr& joy)
{	
	const int BACK_BUTTON = 3;
	prevWiimoteState = curWiimoteState;
	curWiimoteState = joy->buttons[BACK_BUTTON];

	// Just Pressed Wiimote
	if(~prevWiimoteState & curWiimoteState)
	{
		client->Publish("ButtonDown");
	}
	// Just Released Wiimote
	else if(prevWiimoteState & ~curWiimoteState) 
	{
		client->Publish("ButtonUp");
	}
}


// Main
int main(int argc, char* argv[])
{
	// Setup ROS Node
	ros::init(argc, argv, "TCPWiimote");
	ros::NodeHandle nh;
	ros::NodeHandle pnh("~");
	
    // Setup ROS Subscriber
	curWiimoteState = 0;
	prevWiimoteState = 0;
	subscriber = nh.subscribe<sensor_msgs::Joy>("joy", 10, &WiimoteCallBack);
	
	
	// Client Parameters
	std::string ServerIP("127.0.0.1");
	std::string ServerPort("45000");
    std::string PublishTopic("/TCPDefault");
    std::string SubscribeTopic("/TCPDefault");
	
	pnh.getParam("ServerIP", ServerIP);
	pnh.getParam("ServerPort", ServerPort);
	pnh.getParam("PublishTopic", PublishTopic);
	pnh.getParam("SubscribeTopic", SubscribeTopic);


	// Create Client
	client = new TCPLibrary::Client();
	client->Setup(ServerIP, ServerPort, PublishTopic, SubscribeTopic);
    
	ros::spin();
    
	
	// Shutdown Client
	client->Shutdown();
	return 0;
}
