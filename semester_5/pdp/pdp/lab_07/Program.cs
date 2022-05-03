using System;
using System.Diagnostics;
using System.Linq;

namespace lab_07
{
    class Program
    {
        private const int Size = 1000;
        
        static void Main(string[] args)
        {
            MPI.Environment.Run(ref args, communicator =>
            {
                int[] p1 = null;
                int[] p2 = null;

                if (communicator.Rank == 0)
                {
                    p1 = Enumerable.Range(1, Size).ToArray();
                    p2 = Enumerable.Range(Size, 1).ToArray();
                }
                
                communicator.Broadcast(ref p1, 0);
                communicator.Broadcast(ref p2, 0);

                Stopwatch stopwatch = null;
                
                if (communicator.Rank == 0)
                {
                    stopwatch = new Stopwatch();
                    stopwatch.Start();
                }
                
                var product = Product.SimpleParallel(communicator, p1, p2);

                if (communicator.Rank != 0)
                {
                    return;
                }

                stopwatch.Stop();
                // Console.WriteLine($"{string.Join(',', product)}");
                Console.WriteLine($"SimpleParallel: {stopwatch.ElapsedMilliseconds}ms");
            });
        }
    }
}
