using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;
using System.Runtime.InteropServices;

using TCPLibraryCS;

namespace Server
{
    class ServerCSWrapperMain
    {
        static void Main(string[] args)
        {
            String ServerIP = "127.0.0.1";
            String ServerPort = "45000";


            TCPLibraryCS.ServerCS server = new TCPLibraryCS.ServerCS();
            server.Setup(ServerIP, ServerPort);



            while (server.GetIsServerRunning())
            {
                server.Run();
            }
        }
    }
}
