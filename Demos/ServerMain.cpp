// Created by Zachary Metcalf
// zachmetcalf@gmail.com
//
// ServerMain.cpp
// TCPLibrary
//
// Main for ServerTCP
//

#include <TCPLibrary.h>

// Main
int main(const int argc, const char* argv[])
{
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
