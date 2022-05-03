using System;
using System.Linq;
using System.Threading.Tasks;

namespace exam
{
    public static class Program
    {
        private const int Size = 10;
        private const int ThreadCount = 3;
        
        private static void Main()
        {
            var a = Enumerable.Range(1, Size).ToArray();
            var b = Enumerable.Range(1, Size).ToArray();

            var result = new int[a.Length];

            Convolution(a, b, result);
            Console.WriteLine(string.Join(",", result));

            result = new int[a.Length];
            
            Parallel.For(0, ThreadCount, i => ConvolutionWorker(a, b, i, result));
            
            Console.WriteLine(string.Join(",", result));
        }

        private static void Convolution(int[] a, int[] b, int[] result)
        {
            for (var k = 0; k < a.Length; k++)
            {
                for (var i = 0; i < a.Length; i++)
                {
                    var index = k - i;

                    if (index < 0)
                    {
                        index += a.Length;
                    }

                    index %= a.Length;
                    
                    result[k] += a[i] * b[index];
                }
            }
        }
        
        private static void ConvolutionWorker(int[] a, int[] b, int thread, int[] result)
        {
            var length = (a.Length / ThreadCount) + 1;
            var start = thread * length;
            var end = start + length;

            for (var k = start; k < end && k < a.Length; k++)
            {
                for (var i = 0; i < a.Length; i++)
                {
                    var index = k - i;

                    if (index < 0)
                    {
                        index += a.Length;
                    }

                    index %= a.Length;
                    
                    result[k] += a[i] * b[index];
                }
            }
        }
    }
}
