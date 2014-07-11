// Created by Zachary Metcalf
// zachmetcalf@gmail.com
//
// TCPSocketSet.h
// TCPLibrary
//
// TCPSocketSet Wrapper Class
//

namespace TCPLibrary
{
	// Cross Platform TCPSocketSet Wrapper Class
	class TCPSocketSet
	{
	public:
		// Default Constructor for TCPSocketSet
		TCPSocketSet();
		// Destructor for TCPSocketSet
		~TCPSocketSet();

		// Clear Socket Set
		void Zero();
		// Set Copying From Other Set to Current Set
		void CopyFrom(std::shared_ptr<TCPSocketSet> inSocketSet);

		// Set Active Socket in Set
		void Set(std::shared_ptr<TCPSocket> inSocket);
		// Clear Active Socket From Set
		void Clear(std::shared_ptr<TCPSocket> inSocket);
		// Check If Socket Is Set
		const int IsSet(std::shared_ptr<TCPSocket> inSocket);

		// Select for Blocking Selection of Sockets to Be Read From or Written To
		const int Select(std::shared_ptr<TCPSocketSet> inSocketSetIn, std::shared_ptr<TCPSocketSet> inSocketSetOut);

	private:
		// Client Implementation Class
		class TCPSocketSetImpl;
		// Pointer to TCPSocket Implementation Class
		std::shared_ptr<TCPSocketSetImpl> mPImpl;
	};
}
