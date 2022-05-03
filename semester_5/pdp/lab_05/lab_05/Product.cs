using System;
using System.Linq;
using System.Threading.Tasks;

namespace lab_05
{
    public static class Product
    {
        public static int[] SimpleSequential(int[] p1, int[] p2)
        {
            var result = new int[p1.Length + p2.Length - 1];

            for (var i = 0; i < p1.Length; i++)
            {
                for (var j = 0; j < p2.Length; j++)
                {
                    result[i + j] += p1[i] * p2[j];
                }
            }

            return result;
        }
        
        public static int[] SimpleParallel(int[] p1, int[] p2)
        {
            var result = new int[p1.Length + p2.Length - 1];

            Parallel.For(0, p1.Length, i =>
            {
                for (var j = 0; j < p2.Length; j++)
                {
                    result[i + j] += p1[i] * p2[j];
                }
            });

            return result;
        }
        
        public static int[] KaratsubaSequential(int[] p1, int[] p2)
        {
            if (p1.Length < 2 || p2.Length < 2)
            {
                return SimpleSequential(p1, p2);
            }
            
            var length = Math.Min(p1.Length, p2.Length) / 2;
            
            var p1Lower = p1[..length];
            var p1Upper = p1[length..];
            
            var p2Lower = p2[..length];
            var p2Upper = p2[length..];

            var z0 = KaratsubaSequential(p1Lower, p2Lower);
            var z2 = KaratsubaSequential(p1Upper, p2Upper);

            var z10 = Add(p1Lower, p1Upper);
            var z11 = Add(p2Lower, p2Upper);
            var z1 = KaratsubaSequential(z10, z11);
            z1 = Subtract(z1, z2);
            z1 = Subtract(z1, z0);

            z2 = Enumerable.Repeat(0, length * 2).Concat(z2).ToArray();
            z1 = Enumerable.Repeat(0, length).Concat(z1).ToArray();

            return Add(z0, Add(z1, z2));
        }
        
        public static int[] KaratsubaParallel(int[] p1, int[] p2)
        {
            if (p1.Length < 2 || p2.Length < 2)
            {
                return SimpleSequential(p1, p2);
            }
            
            var length = Math.Max(p1.Length, p2.Length) / 2;
            
            var p1Lower = p1[..length];
            var p1Upper = p1[length..];
            
            var p2Lower = p2[..length];
            var p2Upper = p2[length..];

            var z0 = Array.Empty<int>();
            var z2 = Array.Empty<int>();
            
            var z1 = Array.Empty<int>();
            
            Parallel.Invoke(() =>
            {
                z0 = KaratsubaParallel(p1Lower, p2Lower);
            },
            () => 
            {
                z2 = KaratsubaParallel(p1Upper, p2Upper);
            },
            () => 
            {
                var z10 = Add(p1Lower, p1Upper);
                var z11 = Add(p2Lower, p2Upper);
                z1 = KaratsubaParallel(z10, z11);
            });
            
            z1 = Subtract(z1, z2);
            z1 = Subtract(z1, z0);

            z2 = Enumerable.Repeat(0, length * 2).Concat(z2).ToArray();
            z1 = Enumerable.Repeat(0, length).Concat(z1).ToArray();

            return Add(z0, Add(z1, z2));
        }
        
        private static int[] Add(int[] p1, int[] p2) 
        {
            var maxLength = Math.Max(p1.Length, p2.Length);
            var result = new int[maxLength];
            
            Array.Resize(ref p1, maxLength);
            Array.Resize(ref p2, maxLength);

            for (var i = 0; i < maxLength; i++)
            {
                result[i] = p1[i] + p2[i];
            }

            return result;
        }
        
        private static int[] Subtract(int[] p1, int[] p2) 
        {
            var maxLength = Math.Max(p1.Length, p2.Length);
            var result = new int[maxLength];
            
            Array.Resize(ref p1, maxLength);
            Array.Resize(ref p2, maxLength);

            for (var i = 0; i < maxLength; i++)
            {
                result[i] = p1[i] - p2[i];
            }

            return result;
        }
    }
}
