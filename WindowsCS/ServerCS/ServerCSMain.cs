// Created by Zachary Metcalf
// zachmetcalf@gmail.com
//
// ServerCSMain.cs
// TCPLibrary
//
// Main for ServerCSTCP
//

using System;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

using TCPLibraryCS;

namespace Server
{
    class ServerCSMain
    {
        // Main
        static void Main(string[] args)
        {
            // Server Parameters
            String ServerIP = "127.0.0.1";
            String ServerPort = "45000";

            // Demo Parameters
            //ServerIP = "127.0.0.1";


            // Create Server
            TCPLibraryCS.ServerCS server = new TCPLibraryCS.ServerCS();
            server.Setup(ServerIP, ServerPort);

            // Run Server Manually
            //while (server.GetIsServerRunning()) { server.RunOnce(); }
            // Run Server Automatically on Separate Thread
            server.Run();

            // Broadcast
            while(server.GetIsServerRunning())
            {
                // Reset Output Message
                String messageToSend = Console.ReadLine();

	            // Broadcast Message
	            server.Broadcast(messageToSend);

	            // Quit
	            if (messageToSend == "quit")
	            {
		            server.SetIsServerRunning(false);
	            }
            }


            // Shutdown Server
            server.Shutdown();
        }
    }
}
