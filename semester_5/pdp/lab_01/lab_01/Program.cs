using System;
using System.Threading;

namespace lab_01
{
    class Program
    {
        private static void Main(string[] args)
        {
            var bank = new Bank();
            bank.Run(Granularity.Account, true);
        }
    }
}