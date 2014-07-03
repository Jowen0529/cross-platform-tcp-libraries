// Created by Zachary Metcalf
// zachmetcalf@gmail.com
//
// ClientCSMain.cs
// TCPLibrary
//
// Main for ClientCSTCP
//

using System;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

using TCPLibraryCS;

namespace Client
{
    class ClientCSMain
    {
        // CallBack Function for Client Subscriber
        public static void SubscriberCallback(System.String inString)
        {
            Console.WriteLine("recv: " + inString);
        }


        // Main
        static void Main(string[] args)
        {
            // Client Parameters
            String ServerIP = "127.0.0.1";
            String ServerPort = "45000";

            // Demo Parameters
            //ServerIP = "127.0.0.1";


            // Create Client
            TCPLibraryCS.ClientCS client = new TCPLibraryCS.ClientCS();
            client.Setup(ServerIP, ServerPort);

            // Run Client Subscriber Automatically on Separate Thread
            // Run with Default CallBack
            //client.Subscribe(null);
            // Run with Custom CallBack
            TCPLibraryCS.CallBackCS callBack = SubscriberCallback;
            client.Subscribe(callBack);
            // Run with No Publisher
            //while (client.GetIsClientRunning()) {}

            // Client Publisher
            while (client.GetIsClientRunning())
            {   
                String message = Console.ReadLine();
                client.Publish(message);
            }

            
            /*
            // Run Client Subscriber Manually
            while (client.GetIsClientRunning())
            {
                String message = "";
                client.SubscribeOnce(ref message);

                if (message.Length > 0)
                {
                    Console.WriteLine(message);
                }
            }
            */

            
            // Shutdown Client
            client.Shutdown();
        }
    }
}
