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
		// Constructor includes Socket and Network ID
		Proxy(std::shared_ptr<TCPSocket> inSocket, const std::string inIP, const int inNetworkID);
		
		// Destructor
		~Proxy();

		// TCPSocket Getter
		inline const std::shared_ptr<TCPSocket> GetTCPSocket() const { return mSocket; }
        
		// IP Getter
		inline const std::string& GetIP() const { return mIP; }
        
		// ID Getter
		inline const int GetID() const { return mNetworkID; }

	private:
		// Client TCPSocket
		std::shared_ptr<TCPSocket> mSocket;

		// Network ID
		int mNetworkID;

		// IP Address
		std::string mIP;

	//block:
		// Constructor Blocked, Requires Parameters
		Proxy() {}
	};
}
