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

// CallBack Function for Client Subscriber
void SubscriberCallback(const std::string& inString)
{
	std::cout << "recv: " << inString << std::endl;
}


// Main
int main(int argc, char* argv[])
{
	// Setup ROS Node
	ros::init(argc, argv, "ClientROS");
	ros::NodeHandle nh("~");
	

	// Client Parameters
	std::string ServerIP("127.0.0.1");
	std::string ServerPort("45000");
	
	nh.getParam("ServerIP", ServerIP);
	nh.getParam("ServerPort", ServerPort);


	// Create Client
	TCPLibrary::Client* client = new TCPLibrary::Client();
	client->Setup(ServerIP, ServerPort);
    
    
	// Client Subscriber Automatically on Separate Thread
	// Run with Default CallBack
	//client->Subscribe(nullptr);
	// Run with Custom CallBack
	TCPLibrary::CallBack callBack = &SubscriberCallback;
	client->Subscribe(callBack);
	// Run with No Publisher
	//while (client->GetIsClientRunning()) {}
    
    
	// Client Publisher
	while (client->GetIsClientRunning())
	{
		// Reset Output Message
		std::string messageToSend;
        std::getline(std::cin, messageToSend);
        
		// Publish Message
		client->Publish(messageToSend);
        
		if (messageToSend == std::string("quit")) { client->SetIsClientRunning(false); }
	}
    
    
	// Run Client Subscriber Manually
	/*
     while (client.GetIsClientRunning())
     {
     // Reset Input Message
     std::string messageToReceive;
     // Subscribe to Message
     client.SubscribeOnce(messageToReceive);
     if (messageToReceive.size())
     {
     std::cout << messageToReceive << std::endl;
     if(messageToReceive == std::string("quit")) { client.SetIsClientRunning(false); }
     }
     }
     */
    
    
	// Shutdown Client
	client->Shutdown();
	return 0;
}

