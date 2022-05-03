using System;
using System.Collections.Generic;
using System.Linq;

namespace lab_02
{
    public static class Extensions {
        public static double NextDouble(
            this Random random,
            double minValue,
            double maxValue)
        {
            return random.NextDouble() * (maxValue - minValue) + minValue;
        }
    }
    public class Program
    {
        private const int VectorSize = 3;
        private const int VectorMin = -10;
        private const int VectorMax = 10;
        
        public static void Main(string[] args)
        {
            var producerConsumer = new ProducerConsumer();
            var random = new Random();
            List<int> vector1 = Enumerable.Range(0, VectorSize)
                .Select(r => random.Next(VectorMin, VectorMax))
                .ToList();
            List<int> vector2 = Enumerable.Range(0, VectorSize)
                .Select(r => random.Next(VectorMin, VectorMax))
                .ToList();
            double sum = producerConsumer.Run(vector1, vector2);
            
            Console.WriteLine(string.Join(", ", vector1));
            Console.WriteLine(string.Join(", ", vector2));
            Console.WriteLine(sum);
        }
    }
}