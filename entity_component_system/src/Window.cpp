#include "Window.hpp"

Window::Window(const char * title, unsigned int width, unsigned int height)
    : m_deltaTime(0.0f), m_lastFrameTime(0.0f)
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

    /***************************************
     * Create GLFW window for rendering
    ***************************************/
    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (m_window == nullptr)
    {
        std::cout << "Failed to create the GLFW framework window.\n";
        glfwTerminate();
    }

    // Tell GLFW to make the context of our window the main context on the current thread
    glfwMakeContextCurrent(m_window);

    /****************************************
     * Set up GLEW (GL Extension Wrangler)
    ****************************************/
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
        std::cout << "Failed to initialize GLEW.\n";

    // Tell OpenGL the size of the rendering window.
    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);

    // Set the GLFW function pointer for key events
    glfwSetKeyCallback(m_window, keyCallback);
}

Window::~Window()
{
    glfwTerminate();
}

void Window::beginDraw()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLfloat currentFrameTime = glfwGetTime();
    m_deltaTime = currentFrameTime - m_lastFrameTime;
    m_lastFrameTime = currentFrameTime;
}

void Window::endDraw()
{
    glfwSwapBuffers(m_window);
}

void Window::update()
{
    glfwPollEvents();
}

void Window::draw(Drawable * drawable)
{
    drawable->draw();
}

GLfloat Window::getElapsedTime()
{
    return m_deltaTime;
}

bool Window::isDone()
{
    return glfwWindowShouldClose(m_window) > 0;
}

void Window::close()
{
    glfwSetWindowShouldClose(m_window, GL_TRUE);
}

void Window::keyCallback(GLFWwindow * window, int key, int scanCode, int action, int mode)
{
    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, GL_TRUE);
    }    
}
