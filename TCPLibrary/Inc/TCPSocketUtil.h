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

		// Select for Blocking Selection of Sockets to Be Read From or Written To
		const int Select(void* inSetIn, void* inSetOut);
		// Clear Socket Set
		void Zero(void* inSet);
		// Set Copying to Other Set
		void Copy(void* inDst, void* inSrc);

		// Server & Client Socket Creation and Initialization
		std::shared_ptr<TCPSocket> CreateSocket(const std::string& inIP, const std::string& inPort) const;

    private:
        // TCPSocketUtil Implementation Class
        class TCPSocketUtilImpl;
        // Pointer to TCPSocketUtil Implementation Class
        std::shared_ptr<TCPSocketUtilImpl> mPImpl;
	};
}
