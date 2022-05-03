using System.Collections.Generic;

namespace lab_03
{
    public static class Vector
    {
        public static int Dot(List<int> a, List<int> b)
        {
            var result = 0;
            
            for (var i = 0; i < a.Count; i++)
            {
                result += a[i] * b[i];
            }

            return result;
        }
    }
}