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
	ros::init(argc, argv, "ServerROS");
	ros::NodeHandle nh("~");
    
    // Setup ROS Publisher
	publisher = nh.advertise<std_msgs::String>("/TCPROS", 1000);
	
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
    
    
	// Create Client
	TCPLibrary::Client* client = new TCPLibrary::Client();
	client->Setup(ServerIP, ServerPort);
    
    
	// Client Subscriber Automatically on Separate Thread
	// Run with Custom CallBack
	TCPLibrary::CallBack callBack = &SubscriberCallback;
	client->Subscribe(callBack);
	
    
	// Run Server and Client on Separate Threads
	while (server->GetIsServerRunning() || client->GetIsClientRunning())
	{
        
	}
    
    
	// Shutdown Server
	client->Shutdown();
	server->Shutdown();
	return 0;
}

