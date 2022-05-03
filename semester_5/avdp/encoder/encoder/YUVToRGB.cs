using ComputeSharp;

namespace encoder
{
    [AutoConstructor]
    public readonly partial struct YUVToRGB: IComputeShader
    {
        private readonly ReadWriteBuffer<int> xBuffer;
        private readonly ReadWriteBuffer<int> yBuffer;
        private readonly ReadWriteBuffer<int> zBuffer;

        public void Execute()
        {
            int y = xBuffer[ThreadIds.X];
            int u = yBuffer[ThreadIds.X];
            int v = zBuffer[ThreadIds.X];

            y -= 16;
            u -= 128;
            v -= 128;
            
            xBuffer[ThreadIds.X] = (int)(1.164 * y + 0 * u + 1.596 * v);
            yBuffer[ThreadIds.X] = (int)(1.164 * y + -0.392 * u + -0.813 * v);
            zBuffer[ThreadIds.X] = (int)(1.164 * y + 2.017 * u + 0 * v);
        }
    }
}