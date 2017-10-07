//
//  main.cpp
//  GamblersDice
//
//  Created by Bootsmann Games on 20.07.17.
//  Copyright © 2017 Bootsmann Games. All rights reserved.
//

#include "GamblersDice.hpp"
#include <iostream>
#include <chrono>

int main(int argc, const char * argv[])
{
	auto start = std::clock();
	
    constexpr unsigned int size = 6;
    constexpr auto count = 100'000;
    
    GamblersDice dice{size};
    std::vector<int> results(size, 0);
    
    for (auto i = 0; i < count; ++i)
    {
        auto res = dice.roll();
        
        ++results[res - 1];
        std::cout << "result is: " << res << std::endl;
    }
    
    std::cout << "Expected: " << count/size << std::endl;
    
    for (const auto & r : results)
        std::cout << " " << r << std::endl;
	
	auto end = std::clock();
	auto total = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	std::cout << "Total time taken: " << total << std::endl;
	
    return 0;
}
