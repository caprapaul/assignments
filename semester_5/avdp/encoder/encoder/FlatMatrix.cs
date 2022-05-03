namespace encoder
{
    public class FlatMatrix<T>
    {
        public int Width { get; }
        public int Height { get; }

        public T[] Values { get; }

        public FlatMatrix(int width, int height)
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
        
        public T this[int x, int y]
        {
            get => Values[(y * Width) + x];
            set => Values[(y * Width) + x] = value;
        }
        
        public FlatMatrix<T> GetSubMatrix(int x, int y, int width, int height)
        {
            var subMatrix = new FlatMatrix<T>(width, height);

            for (int i = 0; i < width; i++)
            {
                for (int j = 0; j < height; j++)
                {
                    subMatrix[i, j] = this[x + i, y + j];
                }
            }

            return subMatrix;
        }
        
        public void SetSubMatrix(int x, int y, FlatMatrix<T> subMatrix)
        {
            for (int i = 0; i < subMatrix.Width; i++)
            {
                for (int j = 0; j < subMatrix.Height; j++)
                {
                     this[x + i, y + j] = subMatrix[i, j];
                }
            }
        }
    }
}