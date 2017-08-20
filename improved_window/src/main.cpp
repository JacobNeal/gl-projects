#include "Window.hpp"
#include "Triangle.hpp"

int main()
{
    Window window("OpenGL Window", 800, 640);

    Triangle triangle;   

    while (!window.isDone())
    {
        window.beginDraw();
        window.draw(&triangle);
        window.update();
        window.endDraw();
    }

    return 0;
}
