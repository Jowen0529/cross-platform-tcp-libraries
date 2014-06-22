// Created by Zachary Metcalf
// zachmetcalf@gmail.com
//
// ClientMain.cpp
// TCPLibrary
//
// Main for Client
//

#include <TCPLibrary.h>

// CallBack Function for Client Subscriber
void SubscriberCallback(const std::string& inString)
{
	std::cout << "recv: " << inString << std::endl;
}

// Main
int main(const int argc, const char* argv[])
{
	// Client Parameters
	std::string ClientIP("127.0.0.1");
	std::string ServerIP("127.0.0.1");
	std::string ServerPort("45000");
	//std::string ClientIP("127.0.0.1");
	//std::string ServerIP("127.0.0.1");
	//std::string ServerPort("45000");


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
		std::cin >> messageToSend;

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
