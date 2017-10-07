using System;
using System.Collections.Generic;

class Program
{
    static void Main(string[] args)
    {
        var start = DateTime.Now;

        const uint size = 6;
        const uint count = 100000;

        var dice = new GamblersDice(size);
        var results = new List<int>();
        for (int i = 0; i < size; ++i)
        {
            results.Add(0);
        }

        for (int i = 0; i < count; ++i)
        {
            var res = dice.Roll();

            results[(int) res - 1] += 1;
            Console.WriteLine($"result is: {res}");
        }

        Console.WriteLine($"Expected: {count/size}");

        foreach (var r in results)
        {
            Console.WriteLine($" {r}");
        }

        var end = DateTime.Now;
        var total = end - start;
        Console.WriteLine($"Total time taken: {total}");
    }
}
