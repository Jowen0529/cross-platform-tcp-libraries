﻿// Created by Zachary Metcalf
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


            // Create Server
            TCPLibraryCS.ServerCS server = new TCPLibraryCS.ServerCS();
            server.Setup(ServerIP, ServerPort);


            // Run Server
            while (server.GetIsServerRunning())
            {
                server.Run();
            }


            // Shutdown Server
            server.Shutdown();
        }
    }
}