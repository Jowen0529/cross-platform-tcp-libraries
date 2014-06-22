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
	// Client Class
	class Client
	{
	public:
		// Client Constructor
		Client();
		// Client Destructor
		~Client();

		// Setup Client Node with Client IP, Server IP, and Server Port
		const int Setup(const std::string inClientIP, const std::string inServerIP, const std::string inServerPort);
		// Client Shutdown
		const int Shutdown();

		// Run Client Publisher Node
		void Publish(const std::string& inMessageToSend) const;

		// Run Client Subscriber Node
		void Subscribe(std::string& inMessageToRecv) const;
		// Run Client Subscriber Node with CallBack Function
		void Subscribe(CallBack inCallBack);
		
		// Set Client Running
		inline void SetIsClientRunning(const bool inIsClientRunning) { isClientRunning = inIsClientRunning; }
		// Get Client Running
		inline const bool GetIsClientRunning() const { return isClientRunning; }

	private:
		// Client Implementation Class
		class ClientImpl;
		// Pointer to TCPSocket Implementation Class
		std::shared_ptr<ClientImpl> mPImpl;

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
	};
}
