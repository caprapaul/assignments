using System;
using ComputeSharp;

namespace encoder
{
    public class Decoder
    {
        public Image Decode(ImageBlocks imageBlocks)
        {
            Image image = FromBlocks(imageBlocks);
            YUVToRGB(image);

            return image;
        }
        
        private static void YUVToRGB(Image image)
        {
            using ReadWriteBuffer<int> xBuffer = Gpu.Default.AllocateReadWriteBuffer(image.X.Values);
            using ReadWriteBuffer<int> yBuffer = Gpu.Default.AllocateReadWriteBuffer(image.Y.Values);
            using ReadWriteBuffer<int> zBuffer = Gpu.Default.AllocateReadWriteBuffer(image.Z.Values);
            Gpu.Default.For(image.X.Width * image.X.Height, new YUVToRGB(xBuffer, yBuffer, zBuffer));
            
            xBuffer.CopyTo(image.X.Values);
            yBuffer.CopyTo(image.Y.Values);
            zBuffer.CopyTo(image.Z.Values);
        }

        private static Image FromBlocks(ImageBlocks imageBlocks)
        {
            var image = new Image(imageBlocks.Width, imageBlocks.Height);
            
            foreach (Block block in imageBlocks.Blocks)
            {
                switch (block.Type)
                {
                    case BlockType.Y:
                        image.X.SetSubMatrix(block.Position.x, block.Position.y, block.Values);
                        break;
                    case BlockType.U:
                        image.Y.SetSubMatrix(block.Position.x, block.Position.y, block.Values, 2);
                        break;
                    case BlockType.V:
                        image.Z.SetSubMatrix(block.Position.x, block.Position.y, block.Values, 2);
                        break;
                    default:
                        throw new ArgumentOutOfRangeException();
                }
            }

            return image;
        }
    }
}
