// Created by Zachary Metcalf
// zachmetcalf@gmail.com
//
// ClientSubscriberMain.cpp
// TCPLibrary
//
// Main for ClientSubscriber
//

#include <TCPLibrary.h>

#include "ros/ros.h"
#include "std_msgs/String.h"

int main(int argc, char* argv[])
{
	/*
	// Check for Command Line Errors
	if (argc != 4)
	{
		std::cerr << "Usage: ./ClientSubscriber ClientIP:={IP} ServerIP:={IP} ServerPort:={Port}" << std::endl;
		return 1;
	}
	*/


	// Parse Command Line Paramters
	//std::string ClientIP(argv[1]);
	//std::string ServerIP(argv[2]);
	//std::string ServerPort(argv[3]);
	//ClientIP = ClientIP.substr(ClientIP.find_first_of(":=") + 2, ClientIP.size());
	//ServerIP = ServerIP.substr(ServerIP.find_first_of(":=") + 2, ServerIP.size());
	//ServerPort = ServerPort.substr(ServerPort.find_first_of(":=") + 2, ServerPort.size());

	
	
	// TEMP TEST, REPLACE WITH ROSLAUNCH
	std::string ClientIP("127.0.0.1");
	std::string ServerIP("127.0.0.1");
	std::string ServerPort("45000");	

	//ClientIP = std::string("10.122.206.53");
	//ServerIP = std::string("10.122.202.76");
	
	ClientIP = std::string("192.168.2.163");
	ServerIP = std::string("192.168.2.77");


	// Create Client Subscriber
	TCPLibrary::Client client(ClientIP, ServerIP, ServerPort);
	client.Setup();
	

	////////////////////////////////////////
	// Hook in for Client Subscriber
	
	// Setup ROS Node
	ros::init(argc, argv, "TCPROSPublisher");
	ros::NodeHandle nh;
	
	// Setup ROS Publisher
	ros::Publisher publisher = nh.advertise<std_msgs::String>("TCPOut", 1000);
	
	
	while (client.GetIsClientRunning())
	{
		// Reset Input Message
		std::string messageToReceive;

		// Subscribe to Message
		client.Subscribe(messageToReceive);
		if (messageToReceive.size())
		{
			std::cout << messageToReceive << std::endl;
			
			// Publish to ROS Topic
			if(nh.ok())
			{
				std_msgs::String rosMessage;
				rosMessage.data = messageToReceive;
				
				publisher.publish(rosMessage);
				
				ros::spinOnce();	
			}
		}
		// Escape
		if (messageToReceive == std::string("quit")) 
		{ 
			client.SetIsClientRunning(false); 
		}
	}
	////////////////////////////////////////
	

	client.Shutdown();
	return 0;
}
