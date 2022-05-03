using System.Collections.Generic;

namespace lab_01
{
    public class Account
    {
        public int Id { get; set; }
        public long Balance { get; set; }
        public List<Transfer> Transfers { get; set; } = new();
        public object AccountLock { get; set; } = new();
    }
}