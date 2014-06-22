// Created by Zachary Metcalf
// zachmetcalf@gmail.com
//
// TCPLibraryCS.h
// TCPLibraryCS
//
// DLL Bridge to C# for TCP Project
//

// TCPLibrary
#include <TCPLibrary.h>
using namespace TCPLibrary;

// Platform
using namespace System;
using namespace System::Runtime::InteropServices;


namespace TCPLibraryCS
{
	// CLI CallBack Type Definition for C++
	[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
	public delegate void CallBackCPP(const std::string&);

	// CLI CallBack Type Definition for C#
	[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
	public delegate void CallBackCS(System::String^);


	// Client C# Bridge Class
	public ref class ClientCS
	{
	public:
		// Client C# Constructor
		ClientCS();

		// Setup Client
		int Setup(System::String^ inClientIP, System::String^ inServerIP, System::String^ inServerPort);
		// Shutdown Client
		void Shutdown();

		// Run Client Publisher Node
		void Publish(System::String^ inMessageToSend);
		// Run Client Subscriber Node
		void Subscribe(System::String^% inMessageToRecv);

		// Run Client Subscriber Node with CallBack Function
		void Subscribe(CallBackCS^ inDelegate);

		// Get Client Running
		bool GetIsClientRunning();

	private:
		// Default CallBackCPP for Subscriber Threads
		void ClientCS::DefaultCallBackCPP(const std::string& inString);
		// Default CallBackCS for Subscriber Threads
		void ClientCS::DefaultCallBackCS(System::String^ inString);
		// CS CallBack
		CallBackCS^ mCallBackCS;
		// CPP CallBack
		CallBackCPP^ mCallBackCPP;

		// Pointer to C++ Client
		TCPLibrary::Client* mPImpl;
	};


	// Server C# Bridge Class
	public ref class ServerCS
	{
	public:
		// Server C# Constructor
		ServerCS();
			
		// Setup Server
		int Setup(System::String^ inServerIP, System::String^ inServerPort);
		// Shutdown Server
		void Shutdown();

		// Run Server
		int Run();

		// Get Server Running
		bool GetIsServerRunning();

	private:
		// Pointer to C++ Server
		TCPLibrary::Server* mPImpl;
	};
}
