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
            String PublishTopic = "/TCPDefault";
            String SubscribeTopic = "/TCPDefault";

            // Demo Parameters
            //ServerIP = "127.0.0.1";
            //PublishTopic = "/TCPDefault";
            //SubscribeTopic = "/TCPDefult";


            // Create Client
            TCPLibraryCS.ClientCS client = new TCPLibraryCS.ClientCS();
            client.Setup(ServerIP, ServerPort, PublishTopic, SubscribeTopic);

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
                String messageToSend = Console.ReadLine();
                client.Publish(messageToSend);

                if (messageToSend == "quit")
                {
                    client.SetIsClientRunning(false);
                }
            }


            // Shutdown Client
            client.Shutdown();
        }
    }
}
