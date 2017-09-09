#include "minunit.h"
#include "../Editor.hpp"
#include "../ModelLoader.hpp"
#include <iostream>

LOGGER_DECL

int tests_run = 0;

Editor window("Test", 800, 640);
ModelLoader modelLoader;

Model * testModel = nullptr;

/******************************************************
 * Test loading a model and getting it's vertex count.
******************************************************/
static char * testModelLoader()
{
    testModel = modelLoader.load("test.MODEL");

    mu_assert("testModelLoader Failed: No vertices were loaded from the test model.\n", testModel->getVertexCount() > 0);

    mu_assert("testModelLoader Failed: No indices were loaded from the test model.\n", testModel->getIndexCount() > 0);

    return 0;
}

/**********************************************************
 * Test drawing model and ensuring the window is still open.
**********************************************************/
static char * testDrawModelWindowOpen()
{
    testModel = modelLoader.load("test.MODEL");

    mu_assert("testDrawModelWindowOpen Failed: Window is never open to begin with.", !window.isDone());

    window.beginDraw();
    window.update();

    window.draw(testModel);

    window.endDraw();

    mu_assert("testDrawModelWindowOpen Failed: Window closed during the drawing of the model.", !window.isDone());

    return 0;
}

/***********************************************
 * Test to make sure the window is not closing.
************************************************/
static char * testWindowIsNotDone()
{
    mu_assert("testWindowIsNotDone Failed: Window should not be done.", window.isDone() == false);

    return 0;
}

/**************************************************
 * Test that the elapsed time for the window changes.
***************************************************/
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

    mu_assert("testWindowElapsedTime Failed: Elapsed time not updating.", elapsedTimeInitial != elapsedTimeFinal);

    return 0;
}

/***********************************************
 * Test that the window closes.
***********************************************/
static char * testWindowClose()
{
    mu_assert("testWindowClose Failed: Window is already closed.", !window.isDone());

    window.close();

    mu_assert("testWindowClose Failed: Window is not closing.", window.isDone());

    return 0;
}

static char * runAllTests()
{
    mu_run_test(testModelLoader);
    mu_run_test(testDrawModelWindowOpen);

    mu_run_test(testWindowIsNotDone);
    mu_run_test(testWindowElapsedTime);
    mu_run_test(testWindowClose);
    return 0;
}

void testCleanUp()
{
    if (testModel != nullptr)
        delete testModel;
}

int main()
{
    char * result = runAllTests();
    testCleanUp();

    if (result != 0)
        std::cout << result;
    else
        std::cout << "ALL TESTS PASSED.\n";

    std::cout << "Tests run: " << tests_run << "\n\n";

    return result != 0;
}

