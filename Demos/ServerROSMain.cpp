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
	ros::NodeHandle nh;
	
	// Server Parameters
	std::string ServerIP("127.0.0.1");
	std::string ServerPort("45000");
    
    //ServerIP = std::string(argv[1]);
    //ServerPort = std::string(argv[2]);


	// Create Server
	TCPLibrary::Server server;
	server.Setup(ServerIP, ServerPort);


	// Run Server
	while (server.GetIsServerRunning())
	{
		server.Run();
	}


	// Shutdown Server
	server.Shutdown();
	return 0;
}
