cmake_minimum_required(VERSION 3.11)

# Test executables
add_executable(prng-test-stdout "prng-test-stdout.cpp")
add_executable(prng-test-ranges "prng-test-ranges.cpp")

target_link_libraries(prng-test-stdout PRIVATE prng)
target_link_libraries(prng-test-ranges PRIVATE prng)

# Language properties
set_property(TARGET prng-test-stdout PROPERTY CXX_STANDARD 11)
set_property(TARGET prng-test-ranges PROPERTY CXX_STANDARD 11)

set_property(TARGET prng-test-stdout PROPERTY CXX_STANDARD_REQUIRED TRUE)
set_property(TARGET prng-test-ranges PROPERTY CXX_STANDARD_REQUIRED TRUE)

set_property(TARGET prng-test-stdout PROPERTY CXX_EXTENSIONS FALSE)
set_property(TARGET prng-test-ranges PROPERTY CXX_EXTENSIONS FALSE)

# Verbose compiler warnings
if(MSVC)
	target_compile_options(prng-test-stdout PRIVATE /W4 /WX)
	target_compile_options(prng-test-ranges PRIVATE /W4 /WX)
else()
	target_compile_options(prng-test-stdout PRIVATE -Wall -Wextra -Werror -pedantic)
	target_compile_options(prng-test-ranges PRIVATE -Wall -Wextra -Werror -pedantic)
endif()
