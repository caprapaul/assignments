using System;
using System.Diagnostics;

namespace lab_03
{
    public static class Program
    {
        private const int MatrixSize = 9;
        private const int MatrixMin = 0;
        private const int MatrixMax = 2;
        
        private static void Main(string[] args)
        {
            var random = new Random();
            var matrix1 = new FlatMatrix<int>(MatrixSize, MatrixSize);
            var matrix2 = new FlatMatrix<int>(MatrixSize, MatrixSize);

            for (uint i = 0; i < MatrixSize * MatrixSize; i++)
            {
                matrix1[i] = random.Next(MatrixMin, MatrixMax + 1);
                matrix2[i] = random.Next(MatrixMin, MatrixMax  +1);
            }

            var stopwatch = new Stopwatch();
            stopwatch.Start();
            
            FlatMatrix<int> result = Matrix.Dot(matrix1, matrix2);
            // FlatMatrix<int> result = Matrix.DotPool(matrix1, matrix2);
            
            stopwatch.Stop();

            Console.WriteLine(matrix1);
            Console.WriteLine(matrix2);
            Console.WriteLine(result);
            Console.WriteLine($"Elapsed: {stopwatch.ElapsedMilliseconds}ms");
        }
    }
}