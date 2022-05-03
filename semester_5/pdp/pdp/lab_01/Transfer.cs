namespace lab_01
{
    public struct Transfer
    {
        public long Id { get; set; }
        public Account Sender { get; set; }
        public Account Receiver { get; set; }
        public int Amount { get; set; }
    }
}