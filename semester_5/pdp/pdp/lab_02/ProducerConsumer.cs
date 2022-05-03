using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

namespace lab_02
{ 
    using Type = Int32;
    public class ProducerConsumer
    {
        private readonly object _lock = new();
        private readonly Queue<Type> _queue = new();
        private bool _finished = false;

        public Type Run(List<Type> vector1, List<Type> vector2)
        {
            Type sum = 0;
            var vector1Copy = new List<Type>(vector1);
            var vector2Copy = new List<Type>(vector2);
            
            var producer = new Thread(() => Produce(vector1Copy, vector2Copy));
            var consumer = new Thread(() => sum = Consume());
            
            producer.Start();
            consumer.Start();

            producer.Join();
            consumer.Join();

            return sum;
        }

        private void Produce(List<Type> vector1, List<Type> vector2)
        {
            while (vector1.Any())
            {
                int index = vector1.Count - 1;
                Type product = vector1[index] * vector2[index];
                
                vector1.RemoveAt(index);
                vector2.RemoveAt(index);
                
                lock (_lock)
                {
                    _queue.Enqueue(product);
                    Monitor.Pulse(_lock);
                }
            }

            _finished = true;
        }
 
        private Type Consume()
        {
            Type sum = 0;
            
            while (!_finished || _queue.Any())
            {
                lock (_lock)
                {
                    while (!_queue.Any())
                    {
                        Monitor.Wait(_lock);
                    }

                    sum += _queue.Dequeue();
                }
            }

            return sum;
        }
    }
}