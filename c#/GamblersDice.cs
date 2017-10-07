using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;

public class GamblersDice
{
    private List<int> _distributions;
    private Random _rand = new Random();

    public GamblersDice(uint size = 6)
    {
        _distributions = new List<int>((int) size);
        for (var i = 0; i < size; ++i)
        {
            _distributions.Add(1);
        }
    }

    public uint Roll()
    {
        // [  1,   3,   2]
        // [0-1, 1-4, 4-6]
        var sum = _distributions.Sum();
        var r = _rand.NextDouble() * sum;
        int runningSum = 0;
        int result = -1;

        for (var i = 0; i < _distributions.Count; ++i)
        {
            runningSum += _distributions[i];

            if (r < runningSum && result == -1)
            {
                result = i;
                _distributions[i] = 1;
            }
            else
            {
                _distributions[i]++;
            }
        }

        // Add 1, so the die roll is between 1 -> size of die
        return (uint) (result + 1);
    }
}
