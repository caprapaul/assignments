namespace encoder
{
    public class Block
    {
        public const int Size = 8;
        
        public (int x, int y) Position { get; set; }
        public FlatMatrix<int> Values { get; set; }
        public BlockType Type { get; set; }
    }
}
