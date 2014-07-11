// Created by Zachary Metcalf
// zachmetcalf@gmail.com
//
// TCPSocketUtil.h
// TCPLibrary
//
// Cross Platform TCP Socket Interface Utility Wrapper Class
//

namespace TCPLibrary
{
	// Cross Platform TCP Socket Interface Utility Wrapper Class
	class TCPSocketUtil
	{
	public:
		// Default Constructor for TCPSocketUtil
		TCPSocketUtil();   
		// Destructor for TCPSocketUtil
		~TCPSocketUtil();
        
		// Socket Library Initialization
		// returns 0 or error code
        const int Startup() const;
		// Socket Library Shutdown
		// Shuts Down and Returns Error Code
        const int Shutdown() const;
		// Socket Library Error Reporting
		// returns last error code
        const int GetError() const;
		// Socket Library Cleanup
		// returns 0 or error code
		const int CleanUp() const;

		// Server & Client Socket Creation and Initialization
		std::shared_ptr<TCPSocket> CreateSocket(const std::string& inIP, const std::string& inPort) const;

    private:
        // TCPSocketUtil Implementation Class
        class TCPSocketUtilImpl;
        // Pointer to TCPSocketUtil Implementation Class
        std::shared_ptr<TCPSocketUtilImpl> mPImpl;
	};
}
