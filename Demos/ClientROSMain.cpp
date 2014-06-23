// Created by Zachary Metcalf
// zachmetcalf@gmail.com
//
// ClientROSMain.cpp
// TCPLibrary
//
// Main for ClientROS
//

#include <TCPLibrary.h>

// ROS Includes
#include "ros/ros.h"
#include "std_msgs/String.h"

// ROS Publisher
ros::Publisher publisher;

// CallBack Function for Client Subscriber
void SubscriberCallback(const std::string& inString)
{
	std::cout << "recv: " << inString << std::endl;
	
	// Publish to ROS Topic
	std_msgs::String rosMessage;
	rosMessage.data = inString;
	
	publisher.publish(rosMessage);
	ros::spinOnce();	
}

// Main
int main(int argc, char* argv[])
{
	// Setup ROS Node
	ros::init(argc, argv, "ClientROS");
	ros::NodeHandle nh;
	
	// Setup ROS Publisher
	publisher = nh.advertise<std_msgs::String>("TCPROS", 1000);

	// Client Parameters
	std::string ClientIP("127.0.0.1");
	std::string ServerIP("127.0.0.1");
	std::string ServerPort("45000");
	
	//ClientIP = std::string(argv[1]);
	//ServerIP = std::string(argv[2]);
	//ServerPort = std::string(Argv[3]);


	// Create Client
	TCPLibrary::Client client;
	client.Setup(ClientIP, ServerIP, ServerPort);


	// Client Subscriber and Default CallBack
	//client.Subscribe(nullptr);
	// Client Subscriber and Custom CallBack
	TCPLibrary::CallBack callBack = &SubscriberCallback;
	client.Subscribe(callBack);
	// Client Subscriber with No Publisher
	//while (client.GetIsClientRunning()) {}


	// Client Publisher
	while (client.GetIsClientRunning())
	{
		// Reset Output Message
		std::string messageToSend;
		std::getline(std::cin, messageToSend);

		// Publish Message
		client.Publish(messageToSend);

		if (messageToSend == std::string("quit")) { client.SetIsClientRunning(false); }
	}


	// Client Subscriber
	/*
	while (client.GetIsClientRunning())
	{
		// Reset Input Message
		std::string messageToReceive;

		// Subscribe to Message
		client.Subscribe(messageToReceive);
		if (messageToReceive.size())
		{
			std::cout << messageToReceive << std::endl;

			if(messageToReceive == std::string("quit")) { client.SetIsClientRunning(false); }
		}
	}
	*/


	// Shutdown Client
	client.Shutdown();
	return 0;
}
