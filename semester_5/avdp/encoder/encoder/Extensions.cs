using System.IO;
using System.Text;

namespace encoder
{
    public static class Extensions
    {
        public static string? ReadLine(this BinaryReader reader)
        {
            var result = new StringBuilder();
            bool foundEndOfLine = false;
            char ch;
            while (!foundEndOfLine)
            {
                try
                {
                    ch = reader.ReadChar();
                }
                catch (EndOfStreamException ex)
                {
                    if (result.Length == 0) return null;
                    else break;
                }
                
                switch (ch)
                {
                    case '\r':
                        if (reader.PeekChar() == '\n') reader.ReadChar();
                        foundEndOfLine = true;
                        break;
                    case '\n':
                        foundEndOfLine = true;
                        break;
                    default:
                        result.Append(ch);
                        break;
                }
            }
            return result.ToString();
        }
        
        public static FlatMatrix<int> GetSubMatrix(this FlatMatrix<int> matrix, int x, int y, int width, int height, int cellSize)
        {
            width /= cellSize;
            height /= cellSize;
            
            var subMatrix = new FlatMatrix<int>(width, height);

            for (var i = 0; i < width; i++)
            {
                for (var j = 0; j < height; j++)
                {
                    var average = 0;
                    
                    for (var k = 0; k < cellSize; k++)
                    {
                        for (var l = 0; l < cellSize; l++)
                        {
                            average += matrix[x + i * cellSize + k, y + j * cellSize + l];
                        }
                    }

                    average /= cellSize * cellSize;
                    
                    subMatrix[i, j] = average;
                }
            }

            return subMatrix;
        }
        
        public static void SetSubMatrix(this FlatMatrix<int> matrix, int x, int y, FlatMatrix<int> subMatrix, int cellSize)
        {
            for (var i = 0; i < subMatrix.Width; i++)
            {
                for (var j = 0; j < subMatrix.Height; j++)
                {
                    for (var k = 0; k < cellSize; k++)
                    {
                        for (var l = 0; l < cellSize; l++)
                        {
                            matrix[x + i * cellSize + k, y + j * cellSize + l] = subMatrix[i, j];
                        }
                    }
                }
            }
        }
    }
}