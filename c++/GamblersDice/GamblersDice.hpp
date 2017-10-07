//TODO: create an UE4 Version with Blueprint support
//TODO: switch to a parallel version?

#pragma once

#include <memory>
#include <random>
#include <iostream>
//#include <experimental/execution>

class GamblersDice
{
private:
	std::vector<unsigned int> _distributions;
	std::random_device _rd;
	std::default_random_engine _generator;
	std::uniform_real_distribution<double> _dist;

public:
	explicit GamblersDice(unsigned int size = 6) :
		_distributions(size, 1),
		_generator(_rd()),
		_dist(0.0, 1.0)
	{};

	unsigned int roll() noexcept
	{
		unsigned int sum = std::accumulate(_distributions.begin(), _distributions.end(), 0);
		
		/* parallel test
		auto const & v = _distributions;
		{
			auto t1 = std::chrono::high_resolution_clock::now();
			double result = std::accumulate(v.begin(), v.end(), 0.0);
			auto t2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> ms = t2 - t1;
			std::cout << std::fixed << "std::accumulate result " << result
			<< " took " << ms.count() << " ms\n";
		}
			
		{
			auto t1 = std::chrono::high_resolution_clock::now();
			double result = std::reduce(std::execution::par, v.begin(), v.end());
			auto t2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> ms = t2 - t1;
			std::cout << "std::reduce result "
			<< result << " took " << ms.count() << " ms\n";
		}
		*/
		
		
		const auto r = _dist(_generator) * sum;
		unsigned int runningSum = 0;
		int result = -1;
		auto size = _distributions.size();
        
		for (auto i = 0; i < size; ++i)
		{
			runningSum += _distributions[i];

			if (r < runningSum && result == -1) {
				result = i;
				_distributions[i] = 1;
			} else {
				_distributions[i] += 1;
			}
		}

		// Add 1, so the dice roll is between 1 -> size of the dice
		return (result + 1);
	}
};
