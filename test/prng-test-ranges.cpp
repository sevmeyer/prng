#include <cstdint>
#include <iostream>
#include <random>
#include <string>

#include "prng/prng.hpp"


template<typename T>
void testRange(std::string name, T bound)
{
	constexpr int numberOfSeeds{100000};
	constexpr int valuesPerSeed{100000};

	std::mt19937 seedGen{42};
	std::uniform_int_distribution<std::uint64_t> seedDist{};

	std::cout << "Testing ranged " << name << "...\n";
	for (int s{0}; s < numberOfSeeds; ++s)
	{
		std::uint64_t seed{seedDist(seedGen)};
		prng::Generator generator{seed};

		for (int i{0}; i < valuesPerSeed; ++i)
		{
			T value{generator.uniform(bound)};
			if (value < static_cast<T>(0) || value >= bound)
			{
				std::cout << "  Out of range!"
					<< "\n  Seed:  " << seed
					<< "\n  Iter:  " << i
					<< "\n  Value: " << value
					<< "\n";
				return;
			}
		}
	}
	std::cout << "  OK\n";
}


int main()
{
	testRange<int>("int", 1000);
	testRange<float>("float", 1.0f);
	testRange<double>("double", 1.0);
}
