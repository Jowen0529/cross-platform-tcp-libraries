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
            String ClientIP = "127.0.0.1";
            String ServerIP = "127.0.0.1";
            String ServerPort = "45000";


            // Create Client
            TCPLibraryCS.ClientCS client = new TCPLibraryCS.ClientCS();
            client.Setup(ClientIP, ServerIP, ServerPort);



            // Client Subscriber and Default CallBack
            //client.Subscribe(null);
            // Client Subscriber and Custom CallBack
            TCPLibraryCS.CallBackCS callBack = SubscriberCallback;
            client.Subscribe(callBack);
            // Client Subscriber with No Publisher
            //while (client.GetIsClientRunning()) {}




            while (client.GetIsClientRunning())
            {   
                String message = Console.ReadLine();

                client.Publish(message);
            }


            
            /*
            // Standard Way to Subscribe to Messages
            while (client.GetIsClientRunning())
            {
                String message = "";
                client.Subscribe(ref message);

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
