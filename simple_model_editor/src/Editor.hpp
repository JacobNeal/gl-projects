#ifndef EDITOR_HPP
#define EDITOR_HPP

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <string>

#include "ModelLoader.hpp"
#include "Model.hpp"
#include "Drawable.hpp"
#include "Camera.hpp"
#include "Logger.hpp"

static bool     windowKeys[1024];
static bool     windowFirstMouse = true;
static GLfloat  windowLastMouseX;
static GLfloat  windowLastMouseY;
static Camera   windowCamera;
static GLuint   windowScroll = 3;

void keyCallback(GLFWwindow * window, int key, int scanCode, int action, int mode);
void mouseCallback(GLFWwindow * window, double xPos, double yPos);
void mouseButtonCallback(GLFWwindow * window, int button, int action, int mods);
void mouseScrollCallback(GLFWwindow * window, double xOffset, double yOffset);
static std::vector<Model *> windowModels;

class Editor
{
    public:
        Editor(const char * title, unsigned int width, unsigned int height);
        ~Editor();

        void beginDraw();
        void endDraw();
        void update();

        bool isDone();
        void close();

        void draw(Drawable * drawable);

        GLfloat getElapsedTime();

    private:
        void move();

        /****************************************
         * Data members
        ****************************************/
        GLFWwindow * m_window;
        
        GLfloat      m_deltaTime;
        GLfloat      m_lastFrameTime;
        GLuint       m_width;
        GLuint       m_height;

        //Camera *     m_camera;
        Model *      m_selectionCube;
};

#endif
