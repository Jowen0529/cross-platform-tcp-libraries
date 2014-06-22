using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;
using System.Runtime.InteropServices;

using TCPLibraryCS;




namespace ClientPublisher
{

    

    class ClientPublisherCSWrapperMain
    {
        public static void DelegateFunction(System.String inString)
        {
            Console.WriteLine("Holy Crap! I got Here");

            Console.WriteLine(inString);
        }

        //public delegate void Del(String message);
        /*
        public static void DelegateMethod(String message)
        {
            Console.WriteLine(message);
        }
        */


        static void Main(string[] args)
        {
            String ClientIP = "127.0.0.1";
            String ServerIP = "127.0.0.1";
            String ServerPort = "45000";


            TCPLibraryCS.ClientCS client = new TCPLibraryCS.ClientCS();
            client.Setup(ClientIP, ServerIP, ServerPort);


            /*
            TCPLibraryCSWrapper.Del handler = DelegateMethod;
            //handler("Hello World");
            */
            
            
            


            TCPLibraryCS.MySecondDelegate handler = DelegateFunction;
            client.SetCallBack(handler);





            client.Subscribe();



            /*
            //Del handler = DelegateMethod;
            //client.Subscribe(handler);
            */


            //TCPLibraryCSWrapper.Del newHandler = DelegateMethod;
            //client.TestSubscribe(newHandler);



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
        }
    }
}
