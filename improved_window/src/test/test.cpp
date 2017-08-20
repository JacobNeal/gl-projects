#include "minunit.h"
#include "../Window.hpp"
#include <iostream>

int tests_run = 0;

Window window("Test", 800, 640);

/****************************************
 * Make sure the window is not closing.
****************************************/
static char * testWindowIsNotDone()
{
    mu_assert("Error: Window should not be done.", window.isDone() == false);

    return 0;
}

/****************************************
 * Test that the elapsed time for the 
 * window changes.
****************************************/
static char * testWindowElapsedTime()
{
    float elapsedTimeInitial = window.getElapsedTime();

    if (!window.isDone())
    {
        window.beginDraw();
        window.update();
        window.endDraw();
    }

    float elapsedTimeFinal = window.getElapsedTime();

    mu_assert("Error: Elapsed time not updating.", elapsedTimeInitial != elapsedTimeFinal);

    return 0;
}

/****************************************
 * Test that the window closes.
****************************************/
static char * testWindowClose()
{
    mu_assert("Error: Window is already closed.", !window.isDone());

    window.close();

    mu_assert("Error: Window is not closing.", window.isDone());

    return 0;
}

static char * runAllTests()
{
    mu_run_test(testWindowIsNotDone);
    mu_run_test(testWindowElapsedTime);
    mu_run_test(testWindowClose);
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

