#include "minunit.h"
#include "../Bitmask.hpp"
#include <iostream>

int tests_run = 0;

Bitmask mask;

/****************************************
 * Test setting the bits for the bitmask class
****************************************/
static char * testBitmaskSetBits()
{
    unsigned int value = 7;

    for (unsigned short bit = 0; bit < 3; ++bit)
        mask.setBit(bit);

    mu_assert("testBitmaskSetBits Failed: Bitmask didn't set bits correctly.\n", mask.getMask() == value);

    return 0;
}

/****************************************
 * Test the Bitmask matching method
****************************************/
static char * testBitmaskMatches()
{
    Bitmask r_value(7);     // 00000011
    mask.setMask(3);        // 00000111

    bool matches = mask.matches(r_value);

    mu_assert("testBitmaskMatches Failed: Bitmask didn't return correctly as matching.\n", matches);

    return 0;
}

static char * runAllTests()
{
    mu_run_test(testBitmaskSetBits);
    mu_run_test(testBitmaskMatches);
    return 0;
}

int main()
{
    char * result = runAllTests();

    if (result != 0)
        std::cout << result;
    else
        std::cout << "ALL TESTS PASSED.\n";

    std::cout << "Tests run: " << tests_run << "\n\n";

    return result != 0;
}

