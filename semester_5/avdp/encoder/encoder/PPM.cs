using System;
using System.IO;

namespace encoder
{
    using Type = Int32;
    public static class PPM
    {
        public static void WriteImage(string path, Image image)
        {
            using var writer = new StreamWriter(path);
            writer.WriteLine("P3");
            writer.WriteLine($"{image.Width} {image.Height}");

            for (int y = 0; y < image.Height; y++)
            {
                for (int x = 0; x < image.Width; x++)
                {
                    writer.WriteLine(image.X[x, y]);
                    writer.WriteLine(image.Y[x, y]);
                    writer.WriteLine(image.Z[x, y]);
                }
            }
        }
        
        public static Image ReadImage(string path)
        {
            using var reader = new BinaryReader(new FileStream(path, FileMode.Open));

            string format = reader.ReadLine();

            string currentLine = reader.ReadLine();

            while (currentLine != null && currentLine.StartsWith("#"))
            {
                currentLine = reader.ReadLine();
            }

            if (currentLine == null)
            {
                return null;
            }

            // Width + Height
            string[] split = currentLine.Split(" ");
            
            int width = int.Parse(split[0]);
            int height = int.Parse(split[1]);
            currentLine = reader.ReadLine();
            
            if (currentLine == null)
            {
                return null;
            }
            
            int max = int.Parse(currentLine);
            
            var image = new Image(width, height);

            switch (format)
            {
                case "P3":
                    ReadTextPixelImage(reader, image);
                    break;
                case "P6":
                    ReadBinaryPixelImage(reader, image);
                    break;
                default:
                    return null;
            }

            return image;
        }

        private static void ReadTextPixelImage(BinaryReader reader, Image image)
        {
            for (int y = 0; y < image.Height; y++)
            {
                for (int x = 0; x < image.Width; x++)
                {
                    Type red = GetNextTextValue(reader);
                    Type green = GetNextTextValue(reader);
                    Type blue = GetNextTextValue(reader);

                    image.X[x, y] = red;
                    image.Y[x, y] = green;
                    image.Z[x, y] = blue;
                }
            }
        }        
        
        private static void ReadBinaryPixelImage(BinaryReader reader, Image image)
        {
            for (int y = 0; y < image.Height; y++)
            {
                for (int x = 0; x < image.Width; x++)
                {
                    Type red = reader.ReadByte();
                    Type green = reader.ReadByte();
                    Type blue = reader.ReadByte();

                    image.X[x, y] = red;
                    image.Y[x, y] = green;
                    image.Z[x, y] = blue;
                }
            }
        }
        
        private static Type GetNextTextValue(BinaryReader reader)
        {
            return Type.Parse(reader.ReadLine() ?? throw new InvalidOperationException());
        }
    }
}