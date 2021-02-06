using System;  
using System.Net;  
using System.Net.Sockets;  
using System.Text;

namespace lab_02
{
    class Program
    {
        static void Main(string[] args)
        {
            StartServer();
        }
        
        public static void StartServer() 
        {  
            // Get Host IP Address that is used to establish a connection  
            // In this case, we get one IP address of localhost that is IP : 127.0.0.1  
            // If a host has multiple addresses, you will get a list of addresses  
            IPAddress ipAddress = IPAddress.Parse("127.0.0.1");  
            TcpListener server = new TcpListener(ipAddress, 7777);
            server.Start();

            while (true)
            {
                Console.WriteLine("Awaiting connection...");
                TcpClient client = server.AcceptTcpClient();
                Console.WriteLine($"{client.ToString()} connected");
                
                NetworkStream stream = client.GetStream();

                byte[] input = new byte[1024];
                stream.Read(input, 0, input.Length);
                string numbersString = Encoding.Default.GetString(input);
                string[] numberStrings = numbersString.Split(',');

                int sum = 0;

                foreach (string numberString in numberStrings)
                {
                    int number = Int32.Parse(numberString);
                    sum += number;
                }

                byte[] output = new byte[1024];
                output = Encoding.Default.GetBytes(sum.ToString());
                stream.Write(output, 0, output.Length);
            }
        }          
    }
}