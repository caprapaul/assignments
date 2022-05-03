using System;

namespace encoder
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            Image image = PPM.ReadImage("nt-P6.ppm")!;
            var encoder = new Encoder();
            var decoder = new Decoder();
            ImageBlocks imageBlocks = encoder.Encode(image);
            Image decoded = decoder.Decode(imageBlocks);
            PPM.WriteImage("output.ppm", decoded);
        }
    }
}