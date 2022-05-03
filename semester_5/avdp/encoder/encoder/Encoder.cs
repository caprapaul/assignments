using System.Collections.Generic;
using ComputeSharp;

namespace encoder
{
    public class Encoder
    {
        public ImageBlocks Encode(Image image)
        {
            RGBToYUV(image);
            return ToBlocks(image);
        }

        private static void RGBToYUV(Image image)
        {
            using ReadWriteBuffer<int> xBuffer = Gpu.Default.AllocateReadWriteBuffer(image.X.Values);
            using ReadWriteBuffer<int> yBuffer = Gpu.Default.AllocateReadWriteBuffer(image.Y.Values);
            using ReadWriteBuffer<int> zBuffer = Gpu.Default.AllocateReadWriteBuffer(image.Z.Values);
            Gpu.Default.For(image.X.Width * image.X.Height, new RGBToYUV(xBuffer, yBuffer, zBuffer));
            
            xBuffer.CopyTo(image.X.Values);
            yBuffer.CopyTo(image.Y.Values);
            zBuffer.CopyTo(image.Z.Values);
        }
        
        private static ImageBlocks ToBlocks(Image image)
        {
            var imageBlocks = new ImageBlocks(image.Width, image.Height);
            
            for (var i = 0; i < image.Width; i += Block.Size)
            {
                for (var j = 0; j < image.Height; j += Block.Size)
                {
                    FlatMatrix<int> y = image.X.GetSubMatrix(i, j, Block.Size, Block.Size);
                    FlatMatrix<int> u = image.X.GetSubMatrix(i, j, Block.Size, Block.Size, 2);
                    FlatMatrix<int> v = image.X.GetSubMatrix(i, j, Block.Size, Block.Size, 2);

                    var yBlock = new Block
                    {
                        Position = (i, j),
                        Type = BlockType.Y,
                        Values = y
                    };
                    
                    var uBlock = new Block
                    {
                        Position = (i, j),
                        Type = BlockType.U,
                        Values = u
                    };
                    
                    var vBlock = new Block
                    {
                        Position = (i, j),
                        Type = BlockType.V,
                        Values = v
                    };

                    imageBlocks.Blocks.Add(yBlock);
                    imageBlocks.Blocks.Add(uBlock);
                    imageBlocks.Blocks.Add(vBlock);
                }
            }

            return imageBlocks;
        }
    }
}