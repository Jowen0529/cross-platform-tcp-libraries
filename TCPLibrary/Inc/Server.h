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

		// Run Server on Separate Thread
		void Run();
		// Run Server Manually
		void RunOnce();

		// Set Server Running
		void SetIsServerRunning(const bool isInServerRunning);
		// Get Server Running
		const bool GetIsServerRunning() const;

	private:     
		// Client Implementation Class
		class ServerImpl;
		// Pointer to TCPSocket Implementation Class
		std::shared_ptr<ServerImpl> mPImpl;
	};
}
