using System.Collections.Generic;

namespace encoder
{
    public class ImageBlocks
    {
        public int Width { get; }
        public int Height { get; }
        public List<Block> Blocks { get; set; } = new();
        
        public ImageBlocks(int width, int height)
        {
            Width = width;
            Height = height;
        }
    }
}
