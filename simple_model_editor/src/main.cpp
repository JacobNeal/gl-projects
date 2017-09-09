#include <iostream>
#include <fstream>

#include "ModelLoader.hpp"
#include "Model.hpp"
#include "Editor.hpp"
#include "Logger.hpp"

LOGGER_DECL

int main()
{
    Editor editor("Simple Model Editor", 800, 640);

    ModelLoader modelLoader;

    while (!editor.isDone())
    {
        editor.beginDraw();
        editor.update();
        editor.endDraw();
    }

    std::cout << LOGGER;

    std::ofstream logFile("log.txt");

    if (logFile.is_open())
    {
        logFile << LOGGER;
        logFile.close();
    }

    return 0;
}
