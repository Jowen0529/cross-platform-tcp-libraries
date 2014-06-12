// Created by Zachary Metcalf
// zachmetcalf@gmail.com
//
// Server.h
// TCPLibrary
//
// Server Header
//

namespace TCPLibrary
{
	class Server
	{
	public:
		// Server Constructor with Port, IP Address, and Node Type
		Server(const std::string inIP, const std::string inPort);

		// Server Destructor
		~Server() {}

		// Setup Server Node
		const int Setup();

		// Run Server Node
		const int Run();

		// Server Shutdown
        const int Shutdown();

		// Set Server Running
		inline void SetIsServerRunning(const bool isInServerRunning) { isServerRunning = isInServerRunning; }
		// Get Server Running
		inline const bool GetIsServerRunning() const { return isServerRunning; }

	private:        
        // Socket Utility Object
        std::unique_ptr<TCPSocketUtil> mSocketUtil;

		// List of Proxies on Server
		std::list< std::shared_ptr<Proxy> > mProxies;

		// Sets for All Sockets
		fd_set setAll;
		// Sets for Incoming Sockets
		fd_set setIncoming;
		// Sets for Outgoing Sockets
		fd_set setOutgoing;

		// Server Socket
		std::shared_ptr<TCPSocket> mServerSocket;

		// Server IP Address
		std::string mIP;

		// Server Port
		std::string mPort;

		// Next Free Network ID
		int mNextNetworkID;

		// Server Status
		bool isServerRunning;

        // Server To Accept New Client
		void AcceptInitNewClient();
        
		// Server To Receive Message From Publisher and Send to Subscribers
		void ReceiveMessageAndSend(std::shared_ptr<Proxy> inProxy);
        
		// Clean Up Any Disconnected Clients
		void Cleanup();
        
		// Client Sockets Cleanup Helper
		std::list< std::shared_ptr<Proxy> > clientsToBeRemoved;

	//block:
		// Constructor Blocked, Require Parameters
		Server() {}
	};
}
