namespace lab_03
{
    public class FlatMatrix<T>
    {
        public uint Width { get; }
        public uint Height { get; }

        public T[] Values { get; }

        public FlatMatrix(uint width, uint height)
        {
            Width = width;
            Height = height;
            Values = new T[width * height];
        }
        
        public FlatMatrix(FlatMatrix<T> matrix)
        {
            Width = matrix.Width;
            Height = matrix.Height;
            Values = new T[matrix.Width * matrix.Height];
            matrix.Values.CopyTo(Values, 0);
        }

        public uint Index1D(uint x, uint y)
        {
            return (y * Width) + x;
        }

        public (uint, uint) Index2D(uint i)
        {
            return (i % Width, i / Width);
        }
        
        public T this[uint x, uint y]
        {
            get => Values[Index1D(x, y)];
            set => Values[Index1D(x, y)] = value;
        }        
        
        public T this[uint i]
        {
            get => Values[i];
            set => Values[i] = value;
        }

        public override string ToString()
        {
            var result = "";
            
            for (uint x = 0; x < Width; x++)
            {
                var row = "";
                
                for (uint y = 0; y < Height; y++)
                {
                    row += this[x, y] + ", ";
                }

                result += row + "\n";
            }

            return result;
        }
    }
}