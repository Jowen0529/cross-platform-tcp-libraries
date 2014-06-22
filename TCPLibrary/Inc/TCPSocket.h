// Created by Zachary Metcalf
// zachmetcalf@gmail.com
//
// TCPSocket.h
// TCPLibrary
//
// Cross Platform TCP Socket Wrapper Class
//

namespace TCPLibrary
{
	// Cross Platform TCP Socket Wrapper Class
	class TCPSocket
	{
	public:
		// TCPSocketUtil WrapperClass
		friend class TCPSocketUtil;
        
		// TCP Destructor Closes Socket
		~TCPSocket();
        
		// Server Socket Bind to Port
		const int Bind(const std::string& inIP, const std::string& inPort) const;
		// Server Socket Listen for Connection
		const int Listen() const;
		// Server Socket Accept Connection
		const std::shared_ptr<TCPSocket> Accept() const;
        
		// Client Socket Connect
		const int Connect(const std::string& inIP, const std::string& inPort) const;
        
		// Client & Server Send Message
		const int Send(const std::string& inMessage) const;
		// Client & Server Receive Message
		const int Receive(std::string& outMessage) const;
        
		// Set Socket as Blocking
		const int SetNonBlocking(bool inShouldNotBlock);
        // Report If Invalid Socket or Socket Errors
		const bool IsSocketError() const;
        
		// Set Active Socket in Set
        void Set(fd_set* inSet) const;
		// Clear Active Socket From Set
        void Clear(fd_set* inSet) const;
		// Check If Socket Is Set
        const int IsSet(fd_set* inSet) const;

	private:
        // TCPSocket Implementation Class
        class TCPSocketImpl;
        // Pointer to TCPSocket Implementation Class
        std::shared_ptr<TCPSocketImpl> mPImpl;
		
        // TCPSocket Constructors through TCPSocket or TCPSocketUtil Only
        TCPSocket(std::shared_ptr<TCPSocketImpl> inPImpl);
        // TCPSocket Constructors through TCPSocket or TCPSocketUtil Only
		TCPSocket();
	};
}
