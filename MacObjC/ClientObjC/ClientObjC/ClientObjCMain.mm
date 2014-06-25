// Created by Zachary Metcalf
// zachmetcalf@gmail.com
//
// ClientObjCMain.mm
// TCPLibrary
//
// Main for ClientObjCTCP
//

#import <Foundation/Foundation.h>
#include <TCPLibrary.h>

// CallBack Function for Client Subscriber
void SubscriberCallback(const std::string& inString)
{
	std::cout << "recv: " << inString << std::endl;
}

// Main
int main(int argc, const char * argv[])
{
    @autoreleasepool
    {
        // Client Parameters
        std::string ClientIP("127.0.0.1");
        std::string ServerIP("127.0.0.1");
        std::string ServerPort("45000");
        
        //ClientIP = std::string(argv[1]);
        //ServerIP = std::string(argv[2]);
        //ServerPort = std::string(argv[3]);
        
        
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
            std::getline(std::cin, messageToSend);
            
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
    }
    return 0;
}

