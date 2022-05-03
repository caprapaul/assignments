using System;
using System.Diagnostics;
using System.Linq;

namespace lab_05
{
    class Program
    {
        private const int Size = 3;
        
        private static void Main(string[] args)
        {
            var p1 = Enumerable.Range(1, Size).ToArray();
            var p2 = Enumerable.Range(Size, 1).ToArray();

            var stopwatch = new Stopwatch();
            
            stopwatch.Start();
            var ss = Product.SimpleSequential(p1, p2);
            stopwatch.Stop();
            Console.WriteLine($"SimpleSequential: {stopwatch.ElapsedMilliseconds}ms");
            
            stopwatch.Restart();
            var sp = Product.SimpleParallel(p1, p2);
            stopwatch.Stop();
            Console.WriteLine($"SimpleParallel: {stopwatch.ElapsedMilliseconds}ms");
            
            stopwatch.Restart();
            var ks = Product.KaratsubaSequential(p1, p2);
            stopwatch.Stop();
            Console.WriteLine($"KaratsubaSequential: {stopwatch.ElapsedMilliseconds}ms");
            
            stopwatch.Restart();
            var kp = Product.KaratsubaParallel(p1, p2);
            stopwatch.Stop();
            Console.WriteLine($"KaratsubaParallel: {stopwatch.ElapsedMilliseconds}ms");
            
            // Console.WriteLine($"{string.Join(',', ss)}");
            // Console.WriteLine($"{string.Join(',', sp)}");
            // Console.WriteLine($"{string.Join(',', ks)}");
            // Console.WriteLine($"{string.Join(',', kp)}");
        }
    }
}
