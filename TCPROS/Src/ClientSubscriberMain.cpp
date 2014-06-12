// Created by Zachary Metcalf
// zachmetcalf@gmail.com
//
// ClientSubscriberMain.cpp
// TCPLibrary
//
// Main for ClientSubscriber
//

#include <TCPLibrary.h>

int main(const int argc, const char* argv[])
{
	// Check for Command Line Errors
	if (argc != 4)
	{
		std::cerr << "Usage: ./ClientSubscriber ClientIP:={IP} ServerIP:={IP} ServerPort:={Port}" << std::endl;
		return 1;
	}


	// Parse Command Line Paramters
	std::string ClientIP(argv[1]);
	std::string ServerIP(argv[2]);
	std::string ServerPort(argv[3]);
	ClientIP = ClientIP.substr(ClientIP.find_first_of(":=") + 2, ClientIP.size());
	ServerIP = ServerIP.substr(ServerIP.find_first_of(":=") + 2, ServerIP.size());
	ServerPort = ServerPort.substr(ServerPort.find_first_of(":=") + 2, ServerPort.size());


	// Create Client Subscriber
	TCPLibrary::Client client(ClientIP, ServerIP, ServerPort);
	client.Setup();
	

	////////////////////////////////////////
	// Hook in for Client Subscriber
	while (client.GetIsClientRunning())
	{
		// Reset Input Message
		std::string messageToReceive;

		// Subscribe to Message
		client.Subscribe(messageToReceive);
		if (messageToReceive.size())
		{
			std::cout << messageToReceive << std::endl;
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
