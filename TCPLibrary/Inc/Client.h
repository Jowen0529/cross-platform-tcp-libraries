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

		// Setup Client Node with Server IP and Server Port
        const int Setup(const std::string inServerIP, const std::string inServerPort, const std::string inPublishTopic, const std::string inSubscribeTopic);
		// Client Shutdown
		const int Shutdown();

		// Run Client Publisher Node Manually
		void Publish(const std::string& inMessageToSend) const;

		// Run Client Subscriber Node Manually
		void SubscribeOnce(std::string& inMessageToRecv) const;
		// Run Client Subscriber Node with CallBack Function
		void Subscribe(CallBack inCallBack);
		
		// Set Client Running
		void SetIsClientRunning(const bool inIsClientRunning);
		// Get Client Running
		const bool GetIsClientRunning() const;

	private:
		// Client Implementation Class
		class ClientImpl;
		// Pointer to TCPSocket Implementation Class
		std::shared_ptr<ClientImpl> mPImpl;
	};
}
