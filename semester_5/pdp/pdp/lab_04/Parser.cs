using System;
using System.Collections.Generic;

namespace lab_04
{
    public interface IParser
    {
        List<string> Urls { get; set; }
        void Run();
    }
}
