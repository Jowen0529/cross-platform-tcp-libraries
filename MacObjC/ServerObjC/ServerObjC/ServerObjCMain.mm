// Created by Zachary Metcalf
// zachmetcalf@gmail.com
//
// ServerObjCMain.mm
// TCPLibrary
//
// Main for ServerObjCTCP
//

#include <TCPLibrary.h>

// CallBack Function for Client Subscriber
void SubscriberCallback(const std::string& inString)
{
	std::cout << "recv: " << inString << std::endl;
}


// Main
int main(int argc, const char* argv[])
{

    @autoreleasepool
    {
        // Server Parameters
        std::string ServerIP("127.0.0.1");
        std::string ServerPort("45000");
        
        // Demo Parameters
        //ServerIP = std::string("127.0.0.1");
        
        
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
    }
    return 0;
}

