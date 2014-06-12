// Created by Zachary Metcalf
// zachmetcalf@gmail.com
//
// ServerMain.cpp
// TCPLibrary
//
// Main for ServerTCP
//

#include <TCPLibrary.h>

int main(const int argc, const char* argv[])
{
	// Check for Command Line Errors
	if (argc != 3) 
	{ 
		std::cerr << "Usage: ./Server ServerIP:={IP} ServerPort:={Port}" << std::endl;
		return 1; 
	}


	// Parse Command Line Paramters
	std::string ServerIP(argv[1]);
	std::string ServerPort(argv[2]);
	ServerIP = ServerIP.substr(ServerIP.find_first_of(":=") + 2, ServerIP.size());
	ServerPort = ServerPort.substr(ServerPort.find_first_of(":=") + 2, ServerPort.size());
	

	// Create Server
	TCPLibrary::Server server(ServerIP, ServerPort);
	server.Setup();


	// Run Server
	while (server.GetIsServerRunning())
	{
		server.Run();
	}


	server.Shutdown();
	return 0;
}
