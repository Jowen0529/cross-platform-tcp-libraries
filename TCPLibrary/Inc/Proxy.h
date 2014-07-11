// Created by Zachary Metcalf
// zachmetcalf@gmail.com
//
// Proxy.h
// TCPLibrary
//
// ClientProxy to Encapsulate Client Data on Server
//

namespace TCPLibrary
{
	// ClientProxy to Encapsulate Client Data on Server
	class Proxy
	{
	public:
		// Constructor for Proxy includes Socket, Network ID, Topics
		Proxy(std::shared_ptr<TCPSocket> inSocket, const std::string inIP, const int inNetworkID,
              const std::string inPublishTopic, const std::string inSubscribeTopic);
		// Destructor for Proxy
		~Proxy();

		// TCPSocket Getter
		inline const std::shared_ptr<TCPSocket> GetTCPSocket() const { return mSocket; }
		// IP Getter
		inline const std::string& GetIP() const { return mIP; }
		// ID Getter
		inline const int GetID() const { return mNetworkID; }
        // Publish Topic Getter
        inline const std::string& GetPublishTopic() const { return mPublishTopic; }
        // Subscribe Topic Getter
        inline const std::string& GetSubscribeTopic() const { return mSubscribeTopic; }

	private:
		// Client TCPSocket
		std::shared_ptr<TCPSocket> mSocket;
		// Network ID
		int mNetworkID;
		// IP Address
		std::string mIP;
        // Publisher Topic
        std::string mPublishTopic;
        // Subscriber Topic
        std::string mSubscribeTopic;        
        
	//block:
		// Constructor Blocked, Requires Parameters
		Proxy() {}
	};
}
