using System;
using System.Collections.Generic;

namespace lab_04
{
    internal static class Program
    {
        private static readonly List<string> Urls = new() {
            "www.cs.ubbcluj.ro/~rlupsa/edu/pdp/index.html",
            "www.regexr.com",
            "www.ctpcj.ro/index.php/ro/"
        };

        private static void Main(string[] args)
        {
            Console.WriteLine("Callback");
            new CallbackParser(Urls).Run();
            Console.WriteLine("\nTask");
            new TaskParser(Urls).Run();
            Console.WriteLine("\nAsync");
            new AsyncParser(Urls).Run();
        }
    }
}
