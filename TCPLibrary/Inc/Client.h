// Created by Zachary Metcalf
// zachmetcalf@gmail.com
//
// Client.h
// TCPLibrary
//
// Client Header
//

namespace TCPLibrary
{
	class Client
	{
	public:
		// Client Constructor with Client IP, Server IP, and Server Port
		Client(const std::string inClientIP, const std::string inServerIP, const std::string inServerPort);

		// Server Destructor
		~Client() {}

		// Setup Client Node
		const int Setup();

		// Run Client Publisher Node
		void Publish(const std::string& inMessageToSend) const;

		// Run Client Subscriber Node
		void Subscribe(std::string& inMessageToRecv) const;

		// Set Client Running
		inline void SetIsClientRunning(const bool inIsClientRunning) { isClientRunning = inIsClientRunning; }
		// Get Client Running
		inline const bool GetIsClientRunning() const { return isClientRunning; }

		// Client Shutdown
        const int Shutdown();

	private:
        // Socket Utility Object
        std::shared_ptr<TCPSocketUtil> mSocketUtil;
        
		// Client Socket
		std::shared_ptr<TCPSocket> mClientSocket;

		// Client IP Address
		std::string mClientIP;

		// Client Port
		std::string mClientPort;

		// Server IP Address
		std::string mServerIP;

		// Server Port
		std::string mServerPort;

		// Client Status
		bool isClientRunning;

	//block:
		// Constructor Blocked, Require Parameters
		Client() {};
	};
}
