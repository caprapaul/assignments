using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using MPI;

namespace lab_08
{
    class Program
    {
        public static void Main(string[] args) {
            MPI.Environment.Run(ref args, communicator =>
            {
                var dsm = new DSM(communicator);
                
                var thread = new Thread(() => Run(communicator, dsm));

                thread.Start();
            
                switch (communicator.Rank)
                {
                    case 0:
                    {
                        dsm.SubscribeTo("a");
                        dsm.SubscribeTo("b");
                        dsm.SubscribeTo("c");
                        
                        dsm.CheckAndReplace("a",0,111);
                        dsm.CheckAndReplace("b",1,222);
                        dsm.CheckAndReplace("c",444, 555);
                        
                        dsm.Close();
                        break;
                    }
                    case 1:
                    {
                        dsm.SubscribeTo("a");
                        dsm.SubscribeTo("b");
                        break;
                    }
                    case 2:
                    {
                        dsm.SubscribeTo("b");
                        dsm.SubscribeTo("c");
                        
                        dsm.CheckAndReplace("c", 2, 444);
                        break;
                    }
                }
                
                thread.Join();
            });
        }

        private static void Run(Communicator communicator, DSM dsm) 
        {
            while (true)
            {
                Console.WriteLine("\nRank " + communicator.Rank + " waiting..\n");
                var messages = new Message[1];

                communicator.Receive(Communicator.anySource, 0, ref messages);
                var message = messages[0];

                switch (message.Tag)
                {
                    case Tag.Close:
                        Console.WriteLine("Rank " + communicator.Rank + " stopped listening...");
                        return;
                    case Tag.Subscribe:
                    {
                        var data = message.Payload;
                        Console.WriteLine("Subscribe message received");
                        Console.WriteLine("Rank " + communicator.Rank + " received: rank " + data.Value + " subscribes to " + data.Var);
                        dsm.SyncSubscription(data.Var, data.Value);
                        break;
                    }
                    case Tag.Update:
                    {
                        var data = message.Payload;
                        Console.WriteLine("Update message received");
                        Console.WriteLine("Rank " + communicator.Rank + " received:" + data.Var + "->" + data.Value);
                        dsm.SetVariable(data.Var, data.Value);
                        break;
                    }
                    case Tag.Error:
                    {
                        var data = message.Payload;
                        Console.WriteLine("ErrorMessage message received");
                        Console.WriteLine("Rank " + communicator.Rank + " received: Process " + data.Value + " tried to update unavailable variable " + data.Var);
                        break;
                    }
                    default:
                        throw new ArgumentOutOfRangeException();
                }
                
                PrintAll(communicator, dsm);
            }
        }

        private static void PrintAll(Communicator communicator, DSM dsm) 
        {
            var sb = new StringBuilder();
            sb.Append("Write all\n");
            sb.Append($"Rank {communicator.Rank} -> a = {dsm.A}, b = {dsm.B}, c = {dsm.C}\n");
            sb.Append("Subscribers: \n");
            
            foreach (var var in dsm.Subscribers.Keys) 
            {
                sb.Append(var).Append("->")
                    .Append(string.Join(',', dsm.Subscribers.GetValueOrDefault(var)))
                    .Append('\n');
            }
            
            Console.WriteLine(sb);
        }
    }
}
