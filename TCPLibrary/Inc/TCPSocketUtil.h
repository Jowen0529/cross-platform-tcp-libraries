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
		// Default Constructor to TCPSocketUtil
		TCPSocketUtil();
        
		// Default Destructor to TCPSocketUtil
		~TCPSocketUtil();
        
		// Socket Library Initialization
		// returns 0 or error code
        const int Startup() const;
        
		// Socket Library Shutdown
		// Shuts Down and Returns Error Code
        const int Shutdown() const;
        
		// Socket Library Cleanup
		// returns 0 or error code
        const int CleanUp() const;
        
		// Socket Library Error Reporting
		// returns last error code
        const int GetError() const;
        
		// Server Select for Blocking Selection of Sockets to Be Read From or Written To
		const int Select(void* inSetIn, void* inSetOut) const;
        
        // Server & Client Socket Creation and Initialization
		// Bind to Port if Server
        std::shared_ptr<TCPSocket> CreateSocket(const std::string& inIP, const std::string& inPort) const;
        
		// Clear Socket Set
		void Zero(fd_set* inSet) const;
        
        // Set Copying to Other Set
		void Copy(fd_set* inDst, fd_set* inSrc);
        
    private:
        // TCPSocketUtil Implementation Class
        class TCPSocketUtilImpl;
        
        // Pointer to TCPSocketUtil Implementation Class
        std::shared_ptr<TCPSocketUtilImpl> mPImpl;
	};
}
