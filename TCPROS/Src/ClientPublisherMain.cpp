// Created by Zachary Metcalf
// zachmetcalf@gmail.com
//
// ClientPublisherMain.cpp
// TCPLibrary
//
// Main for ClientPublisher
//

#include <TCPLibrary.h>

int main(const int argc, const char* argv[])
{
	// Check for Command Line Errors
	if (argc != 4)
	{
		std::cerr << "Usage: ./ClientPublisher ClientIP:={IP} ServerIP:={IP} ServerPort:={Port}" << std::endl;
		return 1;
	}


	// Parse Command Line Paramters
	std::string ClientIP(argv[1]);
	std::string ServerIP(argv[2]);
	std::string ServerPort(argv[3]);
	ClientIP = ClientIP.substr(ClientIP.find_first_of(":=") + 2, ClientIP.size());
	ServerIP = ServerIP.substr(ServerIP.find_first_of(":=") + 2, ServerIP.size());
	ServerPort = ServerPort.substr(ServerPort.find_first_of(":=") + 2, ServerPort.size());


	// Create Client Publisher
	TCPLibrary::Client client(ClientIP, ServerIP, ServerPort);
	client.Setup();


	////////////////////////////////////////
	// Hook in for Client Publisher
	while (client.GetIsClientRunning())
	{
		// Reset Output Message
		std::string messageToSend;
		std::cin >> messageToSend;

		// Publish Message
		client.Publish(messageToSend);

		// Quit
		if (messageToSend == std::string("quit")) 
		{ 
			client.SetIsClientRunning(false); 
		}
	}
	////////////////////////////////////////


	client.Shutdown();
	return 0;
}
