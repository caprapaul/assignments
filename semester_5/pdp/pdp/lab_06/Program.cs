using System;
using System.Diagnostics;

namespace lab_06
{
    class Program
    {
        private static void Main(string[] args)
        {
            var graph = new DirectedGraph(3000);
            var stopwatch = new Stopwatch();
            
            stopwatch.Start();
            var cycle = graph.GetHamiltonianCycle();
            stopwatch.Stop();
            Console.WriteLine($"Elapsed: {stopwatch.ElapsedMilliseconds}ms");
            // Console.WriteLine($"Graph: {graph}");
            // Console.WriteLine($"Cycle: {string.Join(',', cycle)}");
        }
    }
}
