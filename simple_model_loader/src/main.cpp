#include <iostream>

#include "ModelLoader.hpp"
#include "Model.hpp"
#include "Window.hpp"
#include "Logger.hpp"

LOGGER_DECL

int main()
{
    Window window("Simple Model Loader", 800, 640);

    ModelLoader modelLoader;

    Model * model = modelLoader.load("test.MODEL");

    while (!window.isDone())
    {
        window.beginDraw();

        window.update();

        window.draw(model);

        window.endDraw();
    }

    std::cout << LOGGER;

    return 0;
}
