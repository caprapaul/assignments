using System;

namespace encoder
{
    using Type = Int32;
    public class Image
    {
        public FlatMatrix<Type> X { get; }
        public FlatMatrix<Type> Y { get; }
        public FlatMatrix<Type> Z { get; }
        
        public int Width { get; }
        public int Height { get; }
        
        public Image(Image image)
        {
            Width = image.Width;
            Height = image.Height;
            X = new FlatMatrix<Type>(image.X);
            Y = new FlatMatrix<Type>(image.Y);
            Z = new FlatMatrix<Type>(image.Z);
        }

        public Image(int width, int height)
        {
            Width = width;
            Height = height;
            X = new FlatMatrix<Type>(width, height);
            Y = new FlatMatrix<Type>(width, height);
            Z = new FlatMatrix<Type>(width, height);
        }
    }
}