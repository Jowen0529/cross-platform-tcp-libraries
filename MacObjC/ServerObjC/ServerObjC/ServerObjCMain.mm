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
        //ServerIP = std::string("10.120.68.14");
        
        
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
    return 0;
}

