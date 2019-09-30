prng
====

A simple and efficient pseudorandom number generator for C++11,
based on the excellent [sfc64] (0.94) by Chris Doty-Humphrey.
Implemented in a single lightweight header and
shared under the hassle-free [Boost license].

Note that this generator is **not suitable for security purposes**.


Interface
---------

The default constructor tries to collect entropy from
`std::random_device`, `std::chrono::high_resolution_clock`,
and [ASLR]. The quality of this entropy is platform dependent.
Alternatively, a custom uint64 seed can be provided.

    prng::Generator gen{};     // System entropy
    prng::Generator gen{42u};  // Custom seed

The generator produces pseudorandom uint64 values
and can be used with standard distribution classes.

    std::normal_distribution<double> dist{};
    std::cout << gen()     << std::endl;  // Raw output
    std::cout << dist(gen) << std::endl;  // Standard interface

For uniform distributions, the generator offers a
convenient template function `T uniform(T bound)`,
which returns values in the range `[0, bound)`.

    int    i{gen.uniform(6)};    // [0, 6)
    double d{gen.uniform(1.0)};  // [0.0, 1.0)

For integral types, the bound must be in `[0, 2^64)`.
To ensure an efficient and consistent performance,
the function does not perform rejection sampling.
As a result, it has a tiny bias of `bound / 2^64`,
which should be irrelevant for any bound below `2^32`.

For floating-point types, the number of random bits
is limited to `min(mantissa, 63)`.


Tests
-----

Two test executables can be compiled with:

    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make

`prng-test-stdout` writes binary data to stdout for [PracRand].
It has three modes, to test the implementation of sfc64 itself,
as well as the implementations of the uniform distributions.
In my test runs, all three modes passed a length of 1TB.

    ./test/prng-test-stdout raw64   | RNG_test stdin64 -tlmax 1TB -multithreaded
    ./test/prng-test-stdout fDist32 | RNG_test stdin32 -tlmax 1TB -multithreaded
    ./test/prng-test-stdout iDist16 | RNG_test stdin16 -tlmax 1TB -multithreaded

`prng-test-ranges` iterates through a number of seeds and
values, to test if the uniform distributions are in range:

    ./test/prng-test-ranges



[ASLR]: https://en.wikipedia.org/wiki/ASLR
[Boost license]: https://www.boost.org/users/license.html
[PracRand]: http://pracrand.sourceforge.net
[sfc64]: http://pracrand.sourceforge.net
