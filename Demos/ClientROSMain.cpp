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
#include <ros/ros.h>
#include <std_msgs/String.h>

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
	ros::NodeHandle nh("~");
	
    // Setup ROS Publisher
	publisher = nh.advertise<std_msgs::String>("/TCPROS", 1000);
	
	
	// Client Parameters
	std::string ServerIP("127.0.0.1");
	std::string ServerPort("45000");
    std::string PublishTopic("/TCPDefault");
    std::string SubscribeTopic("/TCPDefault");
	
	nh.getParam("ServerIP", ServerIP);
	nh.getParam("ServerPort", ServerPort);
	nh.getParam("PublishTopic", PublishTopic);
	nh.getParam("SubscribeTopic", SubscribeTopic);


	// Create Client
	TCPLibrary::Client* client = new TCPLibrary::Client();
	client->Setup(ServerIP, ServerPort, PublishTopic, SubscribeTopic);
    
    
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
    
    
	// Shutdown Client
	client->Shutdown();
	return 0;
}
