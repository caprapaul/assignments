using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;

namespace lab_03
{
    public static class Matrix
    {
        private const uint ThreadCount = 3;
        
        private static void DotTask(FlatMatrix<int> a, FlatMatrix<int> b, IEnumerable<uint> indices, FlatMatrix<int> result)
        {
            IEnumerable<(uint, uint, uint)> indices2D = indices.Select(index =>
            {
                (uint x, uint y) = result.Index2D(index);
                return (index, x, y);
            });
            
            foreach ((uint index, uint x, uint y) in indices2D)
            {
                var aColumn = new List<int>((int) result.Height);
                var bRow = new List<int>((int) result.Width);

                for (uint i = 0; i < a.Height; i++)
                {
                    aColumn.Add(a[x, i]);
                }
                
                for (uint i = 0; i < b.Width; i++)
                {
                    bRow.Add(b[i, y]);
                }

                result[index] = Vector.Dot(aColumn, bRow);
            }
        }
        
        public static FlatMatrix<int> Dot(FlatMatrix<int> a, FlatMatrix<int> b)
        {
            Debug.Assert(a.Width == b.Height);
            var result = new FlatMatrix<int>(b.Width, a.Height);
            uint length = result.Height * result.Width;
            uint jobsPerThread = length / ThreadCount;

            var threads = new Thread[ThreadCount];

            for (uint i = 0; i < ThreadCount; i++)
            {
                uint i1 = i;
                
                threads[i] = new Thread(_ =>
                {
                    uint start = i1 * jobsPerThread;
                    uint count = Math.Min(jobsPerThread, length - start - 1);
                    IEnumerable<uint> indices = Enumerable.Range((int) start, (int) count)
                        .Select(index => (uint) index);
                    DotTask(a, b, indices, result);
                });
            }
            
            foreach (Thread thread in threads)
            {
                thread.Start();
            }
            
            foreach (Thread thread in threads)
            {
                thread.Join();
            }
            
            return result;
        }
        
        public static FlatMatrix<int> DotPool(FlatMatrix<int> a, FlatMatrix<int> b)
        {
            Debug.Assert(a.Width == b.Height);
            var result = new FlatMatrix<int>(b.Width, a.Height);
            uint length = result.Height * result.Width;
            uint jobsPerThread = length / ThreadCount;
            
            var doneEvents = new ManualResetEvent[ThreadCount];
            
            for (uint i = 0; i < ThreadCount; i++)
            {
                uint i1 = i;
                doneEvents[i] = new ManualResetEvent(false);
                
                ThreadPool.QueueUserWorkItem(_ =>
                {
                    uint start = i1 * jobsPerThread;
                    uint count = Math.Min(jobsPerThread, length - start - 1);
                    IEnumerable<uint> indices = Enumerable.Range((int) start, (int) count)
                        .Select(index => (uint) index);
                    
                    DotTask(a, b, indices, result);
                    
                    doneEvents[i1].Set();
                });
            }

            WaitHandle.WaitAll(doneEvents);
            
            return result;
        }
    }
}