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

// Main
int main(int argc, char* argv[])
{
	// Setup ROS Node
	ros::init(argc, argv, "ServerROS");
	ros::NodeHandle nh("~");
    
	
	// Server Parameters
	std::string ServerIP("127.0.0.1");
	std::string ServerPort("45000");
    
	nh.getParam("ServerIP", ServerIP);
	nh.getParam("ServerPort", ServerPort);

	
	// Create Server
	TCPLibrary::Server* server = new TCPLibrary::Server();
	server->Setup(ServerIP, ServerPort);
    
    
	// Run Server Manually
	//while (server->GetIsServerRunning()) { server->RunOnce(); }
	// Run Server Automatically on Separate Thread
	server->Run();
	
    
	// Broadcast
	while (server->GetIsServerRunning())
	{
		// Reset Output Message
		std::string messageToSend;
		std::getline(std::cin, messageToSend);

		// Broadcast Message
		server->Broadcast(messageToSend);

		// Quit
		if (messageToSend == std::string("quit"))
		{
			server->SetIsServerRunning(false);
		}
	}
    
    
	// Shutdown Server
	server->Shutdown();
	return 0;
}

