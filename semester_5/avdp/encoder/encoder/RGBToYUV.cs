using ComputeSharp;

namespace encoder
{
    [AutoConstructor]
    public readonly partial struct RGBToYUV: IComputeShader
    {
        private readonly ReadWriteBuffer<int> xBuffer;
        private readonly ReadWriteBuffer<int> yBuffer;
        private readonly ReadWriteBuffer<int> zBuffer;

        public void Execute()
        {
            int r = xBuffer[ThreadIds.X];
            int g = yBuffer[ThreadIds.X];
            int b = zBuffer[ThreadIds.X];

            xBuffer[ThreadIds.X] = (int)(0.257 * r + 0.504 * g + 0.098 * b + 16);
            yBuffer[ThreadIds.X] = (int)(-0.148 * r + -0.291 * g + 0.430 * b + 128);
            zBuffer[ThreadIds.X] = (int)(0.439 * r + -0.368 * g + -0.071 * b + 128);
        }
    }
}