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
        // CallBack Function for Client Subscriber
        public static void SubscriberCallback(System.String inString)
        {
            Console.WriteLine("recv: " + inString);
        }


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


            // Create Client
            TCPLibraryCS.ClientCS client = new TCPLibraryCS.ClientCS();
            client.Setup(ServerIP, ServerPort);


            // Client Subscriber Automatically on Separate Thread
            // Run with Custom CallBack
            TCPLibraryCS.CallBackCS callBack = SubscriberCallback;
            client.Subscribe(callBack);


            // Run Server and Client on Separate Threads
            while (server.GetIsServerRunning() || client.GetIsClientRunning())
            {

            }


            // Shutdown Server
            client.Shutdown();
            server.Shutdown();
        }
    }
}
