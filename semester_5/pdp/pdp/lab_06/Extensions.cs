using System;
using System.Collections.Generic;

namespace lab_06
{
    public static class Extensions
    {
        public static void Shuffle<T>(this IList<T> list)
        {
            var n = list.Count;
            
            while (n > 1)
            {
                n--;
                var k = ProgramRandom.Instance.Next(n + 1);
                (list[k], list[n]) = (list[n], list[k]);
            }
        }
    }
}
