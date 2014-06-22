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
	// Server Class
	class Server
	{
	public:
		// Server Constructor with Port, IP Address, and Node Type
		Server();
		// Server Destructor
		~Server();

		// Setup Server Node
		const int Setup(const std::string inIP, const std::string inPort);
		// Server Shutdown
		const int Shutdown();

		// Run Server Node
		const int Run();

		// Set Server Running
		inline void SetIsServerRunning(const bool isInServerRunning) { isServerRunning = isInServerRunning; }
		// Get Server Running
		inline const bool GetIsServerRunning() const { return isServerRunning; }

	private:     
		// Client Implementation Class
		class ServerImpl;
		// Pointer to TCPSocket Implementation Class
		std::shared_ptr<ServerImpl> mPImpl;

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
		std::string mServerIP;
		// Server Port
		std::string mServerPort;
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
	};
}
