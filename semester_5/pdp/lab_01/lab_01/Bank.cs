using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading;

namespace lab_01
{
    public class Bank
    {
        private const int ThreadsCount = 20;
        private const int OperationsCount = 2000000;
        private const int AccountsCount = 1000;
        private const int MinTransfer = 1;
        private const int MaxTransfer = 100;
        private const int TimeBetweenChecks = 100; 

        private List<Account> _accounts;
        private readonly object _bankLock = new();
        private long _transfersCount;

        private long _totalElapsed;
        
        private void ExecuteOperationBank(int senderId, int receiverId, int amount)
        {
            lock (_bankLock)
            {
                Account sender = _accounts[senderId];
                Account receiver = _accounts[receiverId];

                var transfer = new Transfer
                {
                    Id = _transfersCount,
                    Amount = amount,
                    Sender = sender,
                    Receiver = receiver
                };
                
                _transfersCount++;
                
                sender.Balance -= amount;
                sender.Transfers.Add(transfer);

                receiver.Balance += amount;
                receiver.Transfers.Add(transfer);
            }
        }
        
        private void ExecuteOperationAccount(int senderId, int receiverId, int amount)
        {
            Account sender = _accounts[senderId];
            Account receiver = _accounts[receiverId];
            
            Transfer transfer;

            lock (_bankLock)
            {
                transfer = new Transfer
                {
                    Id = _transfersCount,
                    Amount = amount,
                    Sender = sender,
                    Receiver = receiver
                };
                    
                _transfersCount++;
            }

            lock (sender.AccountLock)
            {
                sender.Balance -= amount;
                sender.Transfers.Add(transfer);
            }

            lock (receiver.AccountLock)
            {
                receiver.Balance += amount;
                receiver.Transfers.Add(transfer);
            }
        }
        
        private void ExecuteOperations(int threadId, Action<int, int, int> operation, int operationsCount)
        {
            var stopwatch = new Stopwatch();
            var random = new Random();

            for (var i = 0; i < operationsCount; i++)
            {
                int senderId = random.Next(_accounts.Count);
                int receiverId = senderId;

                while (receiverId == senderId)
                {
                    receiverId = random.Next(_accounts.Count);
                }

                int amount = random.Next(MinTransfer, MaxTransfer);
                
                stopwatch.Start();
                operation(senderId, receiverId, amount);
                stopwatch.Stop();
            }

            Interlocked.Add(ref _totalElapsed, stopwatch.ElapsedMilliseconds);

            Console.WriteLine($"({threadId}) Elapsed: {stopwatch.ElapsedMilliseconds}ms");
        }

        public void Run(Granularity granularity, bool withChecks=true)
        {
            _accounts = Enumerable.Range(0,AccountsCount).Select(i => new Account { Id = i }).ToList();
            var threads = new Thread[ThreadsCount];
            var stopwatch = new Stopwatch();

            Action<int, int, int> execute = granularity switch
            {
                Granularity.Account => ExecuteOperationAccount,
                Granularity.Bank => ExecuteOperationBank,
                _ => throw new ArgumentOutOfRangeException(nameof(granularity), granularity, null)
            }; 
            
            Action consistencyCheck = granularity switch
            {
                Granularity.Account => ConsistencyCheckAccount,
                Granularity.Bank => ConsistencyCheckBank,
                _ => throw new ArgumentOutOfRangeException(nameof(granularity), granularity, null)
            };
            
            stopwatch.Start();
            
            for (var i = 0; i < ThreadsCount; i++)
            {
                int i1 = i;
                var thread = new Thread(() => ExecuteOperations(i1, execute, OperationsCount / ThreadsCount))
                {
                    Name = $"Thread{i}"
                };
                
                thread.Start();
                threads[i] = thread;
            }

            if (withChecks)
            {
                while (CheckThreadsAlive(threads))
                {
                    Thread.Sleep(TimeBetweenChecks);
                    consistencyCheck();
                }
            }
            
            for (var i = 0; i < ThreadsCount; i++)
            {
                threads[i].Join();
            }
            
            stopwatch.Stop();
            
            consistencyCheck();
            
            Console.WriteLine($"Total operations: {OperationsCount}");
            Console.WriteLine($"Total elapsed: {stopwatch.ElapsedMilliseconds}ms");
            Console.WriteLine($"Average elapsed: {_totalElapsed / ThreadsCount}ms");
        }

        private bool CheckThreadsAlive(Thread[] threads)
        {
            foreach (var thread in threads)
            {
                if (!thread.IsAlive)
                {
                    return false;
                }
            }

            return true;
        }
        
        private void ConsistencyCheckBank()
        {
            lock (_bankLock)
            {
                _accounts.ForEach(account =>
                {
                    var sum = account.Transfers.Select(transfer =>
                        (long) (transfer.Receiver.Id == account.Id ? transfer.Amount : -transfer.Amount)).Sum();

                    if (sum != account.Balance)
                    {
                        throw new Exception(
                            $"Invalid balance for account {account.Id}: expected {sum}, found {account.Balance}");
                    }
                });
            }
        }

        private void ConsistencyCheckAccount()
        {
            _accounts.ForEach(account =>
            {
                lock (account.AccountLock)
                {
                    var sum = account.Transfers.Select(transfer =>
                        {
                            lock (transfer.Receiver.AccountLock)
                            {
                                return (long) (transfer.Receiver.Id == account.Id ? transfer.Amount : -transfer.Amount);
                            }
                        }).Sum();

                    if (sum != account.Balance)
                    {
                        throw new Exception(
                            $"Invalid balance for account {account.Id}: expected {sum}, found {account.Balance}");
                    }
                }
            });
        }
    }
}