#include "Editor.hpp"

Editor::Editor(const char * title, unsigned int width, unsigned int height)
    : m_deltaTime(0.0f), m_lastFrameTime(0.0f), m_width(width), m_height(height)
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
        LOG("Failed to create the GLFW framework window.");
        glfwTerminate();
    }

    // Tell GLFW to make the context of our window the main context on the current thread
    glfwMakeContextCurrent(m_window);

    /****************************************
     * Set up GLEW (GL Extension Wrangler)
    ****************************************/
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
        LOG("Failed to initialize GLEW.");

    // Tell OpenGL the size of the rendering window.
    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);

    // Set the GLFW function pointers for events
    glfwSetKeyCallback(m_window, keyCallback);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(m_window, mouseCallback);
    glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
    glfwSetScrollCallback(m_window, mouseScrollCallback);

    //m_camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

    m_selectionCube = ModelLoader::load("selectionCube.MODEL");

    // Resolve bug with macOS window being scaled and setting the wrong glViewport size
    int windowXPos, windowYPos;
    glfwGetWindowPos(m_window, &windowXPos, &windowYPos);
    glfwSetWindowPos(m_window, windowXPos + 1, windowYPos);
}

Editor::~Editor()
{
    //delete m_camera;
    for (Model * model : windowModels)
        delete model;

    delete m_selectionCube;
    glfwTerminate();
}

void Editor::beginDraw()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLfloat currentFrameTime = glfwGetTime();
    m_deltaTime = currentFrameTime - m_lastFrameTime;
    m_lastFrameTime = currentFrameTime;

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    draw(m_selectionCube);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    for (Model * model : windowModels)
        draw(model);
}

void Editor::endDraw()
{
    glfwSwapBuffers(m_window);
}

void Editor::update()
{
    glfwPollEvents();
    move();
}

void Editor::draw(Drawable * drawable)
{
    // Set up matrix transformations
    glm::mat4 view = windowCamera.getViewMatrix();
    glUniformMatrix4fv(glGetUniformLocation(drawable->getShaderProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)m_width / (float)m_height, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(drawable->getShaderProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glm::mat4 model;
    model = glm::translate(model, drawable->getPosition());
    //model = glm::rotate(model, glm::radians((GLfloat)glfwGetTime() * 20.0f), glm::vec3(1.0f, 0.3f, 0.5f));
    glUniformMatrix4fv(glGetUniformLocation(drawable->getShaderProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));

    drawable->draw();
}

GLfloat Editor::getElapsedTime()
{
    return m_deltaTime;
}

bool Editor::isDone()
{
    return glfwWindowShouldClose(m_window) > 0;
}

void Editor::close()
{
    glfwSetWindowShouldClose(m_window, GL_TRUE);
}

void Editor::move()
{
    if (windowKeys[GLFW_KEY_W])
        windowCamera.processKeyboard(CameraMovement::FORWARD, m_deltaTime);
    if (windowKeys[GLFW_KEY_S])
        windowCamera.processKeyboard(CameraMovement::BACKWARD, m_deltaTime);
    if (windowKeys[GLFW_KEY_A])
        windowCamera.processKeyboard(CameraMovement::LEFT, m_deltaTime);
    if (windowKeys[GLFW_KEY_D])
        windowCamera.processKeyboard(CameraMovement::RIGHT, m_deltaTime);

    //glm::vec3 selectionCubePos = m_camera->getPosition() + (m_camera->getFrontVector() * 3.0f);
    glm::vec3 selectionCubePos = windowCamera.getPosition() + (windowCamera.getFrontVector() * (GLfloat)windowScroll);
    
    selectionCubePos.x = glm::round(selectionCubePos.x);
    selectionCubePos.y = glm::round(selectionCubePos.y);
    selectionCubePos.z = glm::round(selectionCubePos.z);

    if (selectionCubePos != m_selectionCube->getPosition())
    {
        m_selectionCube->setPosition(selectionCubePos);

        LOG("Updating selection cube position to: (" +
            std::to_string(selectionCubePos.x) + "," +
            std::to_string(selectionCubePos.y) + "," +
            std::to_string(selectionCubePos.z) + ")");
    }
}

void keyCallback(GLFWwindow * window, int key, int scanCode, int action, int mode)
{
    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, GL_TRUE);
        
        windowKeys[key] = true;       
    }
    else if (action == GLFW_RELEASE)
        windowKeys[key] = false;
}

void mouseCallback(GLFWwindow * window, double xPos, double yPos)
{
    if (windowFirstMouse)
    {
        windowLastMouseX = xPos;
        windowLastMouseY = yPos;
        windowFirstMouse = false;
    }

    GLfloat xOffset = xPos - windowLastMouseX;
    GLfloat yOffset = windowLastMouseY - yPos;

    windowLastMouseX = xPos;
    windowLastMouseY = yPos;

    windowCamera.processMouseMovement(xOffset, yOffset);
}

void mouseButtonCallback(GLFWwindow * window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        glm::vec3 cubePos = windowCamera.getPosition() + (windowCamera.getFrontVector() * (GLfloat)windowScroll);

        cubePos.x = glm::round(cubePos.x);
        cubePos.y = glm::round(cubePos.y);
        cubePos.z = glm::round(cubePos.z);

        if (windowModels.size() == 0 || cubePos != windowModels.back()->getPosition())
        {
            Model * newCube = ModelLoader::load("cube.MODEL");

            newCube->setPosition(cubePos);
            windowModels.push_back(newCube);
            LOG("Added new cube");
        }
    }
}

void mouseScrollCallback(GLFWwindow * window, double xOffset, double yOffset)
{
    if (yOffset > 0)
        windowScroll++;
    else if (yOffset < 0 && windowScroll > 0)
        windowScroll--;
}
