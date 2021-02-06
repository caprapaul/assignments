using System;
using System.Net.Sockets;
using System.Threading;
using System.Timers;

namespace client
{
    public static class Client
    {
        public const string ServerIp = "192.168.100.95";
        public const int ServerPort = 7777;

        private static void Main(string[] args)
        {
            int groupPort = 9090;
            Console.WriteLine("leader?");
            int isLeader = int.Parse(Console.ReadLine());

            if (isLeader == 1)
            {
                HandleLeader(groupPort);
            }
            else
            {
                HandleMember(groupPort);
            }
        }

        private static void HandleLeader(int port)
        {
            while (true)
            {
                SendBroadcast();
                Thread.Sleep(2000);
            }
        }
        
        private static void HandleMember(int port)
        {
            
        }

        private static void SendBroadcast(Socket broadcast) 
        {
            broadcast.SendTo()
        }
    }
}