#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#define WINWIDTH 800
#define WINHEIGHT 640
#define TITLE "OpenGL Window"

void keyCallback(GLFWwindow * window, int key, int scanCode, int action, int mode);

int main()
{
    /****************************************
     * Set up GLFW
    ****************************************/
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    /****************************************
     * Create GLFW window for rendering
    ****************************************/
    GLFWwindow * window = glfwCreateWindow(WINWIDTH, WINHEIGHT, TITLE, nullptr, nullptr);

    if (window == nullptr)
    {
        std::cout << "Failed to create the GLFW framework window.\n";
        glfwTerminate();
    }

    // Tell GLFW to make the context of our window the main context on the current thread
    glfwMakeContextCurrent(window);

    /****************************************
     * Set up GLEW (GL Extension Wrangler)
    ****************************************/
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
        std::cout << "Failed to initialize GLEW.\n";

    // Tell OpenGL the size of the rendering window.
    glViewport(0, 0, WINWIDTH, WINHEIGHT);

    glEnable(GL_DEPTH_TEST);

    // Set the GLFW function pointer for key events
    glfwSetKeyCallback(window, keyCallback);

    GLfloat deltaTime, lastFrame;

    /****************************************
     * Main loop
    ****************************************/
    while (!glfwWindowShouldClose(window))
    {
        // Handle the time since the last frame
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    return 0;
}

void keyCallback(GLFWwindow * window, int key, int scanCode, int action, int mode)
{
    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, GL_TRUE);
    }

}
