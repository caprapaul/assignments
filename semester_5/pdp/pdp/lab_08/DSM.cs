using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using MPI;

namespace lab_08
{
    public class DSM
    {
        public int A;
        public int B;
        public int C;
        public readonly ConcurrentDictionary<string, HashSet<int>> Subscribers;

        private readonly Intracommunicator _communicator;

        public DSM(Intracommunicator communicator)
        {
            _communicator = communicator;
            A = 0;
            B = 1;
            C = 2;
            Subscribers = new ConcurrentDictionary<string, HashSet<int>>();
            Subscribers.TryAdd("a", new HashSet<int>());
            Subscribers.TryAdd("b", new HashSet<int>());
            Subscribers.TryAdd("c", new HashSet<int>());
        }

        private static readonly object Lock = new();

        public void SetVariable(string var, int value)
        {
            switch (var)
            {
                case "a":
                    A = value;
                    break;
                case "b":
                    B = value;
                    break;
                case "c":
                    C = value;
                    break;
            }
        }

        public void CheckAndReplace(string var, int old, int newValue)
        {
            if (!Subscribers.GetValueOrDefault(var).Contains(_communicator.Rank))
            {
                SendToSubscribers(var, new Message
                {
                    Tag = Tag.Error
                });
            }

            switch (var)
            {
                case "a":
                    while (A != old) {}
                    UpdateVariable("a", newValue);
                    break;
                case "b":
                    while (B != old) {}
                    UpdateVariable("b", newValue);
                    break;
                case "c":
                    while (C != old) {}
                    UpdateVariable("c", newValue);
                    break;
            }
        }

        public void SubscribeTo(string var)
        {
            var subscribers = Subscribers.GetValueOrDefault(var);
            subscribers?.Add(_communicator.Rank);
            
            SendAll(new Message
            {
                Tag = Tag.Subscribe,
                Payload = new MessageData
                {
                    Value = _communicator.Rank,
                    Var = var
                }
            });
        }

        public void SyncSubscription(string var, int rank)
        {
            var subscribers = Subscribers.GetValueOrDefault(var);
            subscribers?.Add(rank);
        }

        public void Close()
        {
            SendAll(new Message
            {
                Tag = Tag.Close
            });
        }
        
        private void SendAll(Message message)
        {
            var messages = new[] {message};
            
            for (var i = 0; i < _communicator.Size; i++)
            {
                if (_communicator.Rank == i && message.Tag != Tag.Close)
                {
                    continue;
                }
                
                _communicator.Send(messages, i, 0);
            }
        }
        
        private void SendToSubscribers(string var, Message message)
        {
            var messages = new [] { message };
            
            for (var i = 0; i < _communicator.Size; i++)
            {
                if (_communicator.Rank == i || !Subscribers.GetValueOrDefault(var).Contains(i))
                {
                    continue;
                }
                
                _communicator.Send(messages, i, 0);
            }
        }
        
        private void UpdateVariable(string var, int value)
        {
            lock (Lock) 
            {
                SetVariable(var, value);
                var message = new Message
                {
                    Tag = Tag.Update,
                    Payload = new MessageData
                    {
                        Var = var,
                        Value = value
                    }
                };
                SendToSubscribers(var, message);
            }
        }
    }
}
