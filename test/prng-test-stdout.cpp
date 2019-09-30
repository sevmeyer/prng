#include <cstdint>
#include <cstdio>
#include <array>
#include <iostream>
#include <string>

#include "prng/prng.hpp"


// Produces output for PractRand, based on
// http://www.pcg-random.org/posts/how-to-test-with-practrand.html

int main(int argc, char* argv[])
{
#ifdef _WIN32
	// Turn off newline conversion on Windows (untested)
	std::freopen(nullptr, "wb", stdout);
#endif

	std::string name{(argc == 2) ? argv[1] : ""};
	prng::Generator generator{UINT64_C(0x0123456789ABCDEF)};

	if (name == "raw64")
	{
		// Test raw uint64 output.

		std::array<std::uint64_t, 1024> buffer{};
		while (true)
		{
			for (auto& value : buffer)
				value = generator();
			std::fwrite(buffer.data(), sizeof(buffer[0]), buffer.size(), stdout);
		}
	}

	if (name == "fDist32")
	{
		// Test floating-point distribution function.
		// The output is converted to uint32 for PractRand.
		// This is therefore an approximation, but should
		// detect serious flaws in the implementation.

		std::array<std::uint32_t, 1024> buffer{};
		while (true)
		{
			for (auto& value : buffer)
				value = std::uint32_t(generator.uniform(1.0) * 0xffffffff);
			std::fwrite(buffer.data(), sizeof(buffer[0]), buffer.size(), stdout);
		}
	}

	if (name == "iDist16")
	{
		// Test integer distribution function.
		// The bound of 2^31 is chosen because it
		// - is within the 32bit range (reasonable use case)
		// - does not evenly divide 2^64 (force bias)
		// - can be truncated to uint16 for PractRand
		//   without introducing additional bias.

		std::array<std::uint16_t, 1024> buffer{};
		while (true)
		{
			for (auto& value : buffer)
				value = std::uint16_t(generator.uniform(0x80000000)); // 2^31
			std::fwrite(buffer.data(), sizeof(buffer[0]), buffer.size(), stdout);
		}
	}

	std::cerr << "Invalid test name\n";
	return 1;
}
