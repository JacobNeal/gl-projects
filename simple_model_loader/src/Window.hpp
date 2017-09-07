#ifndef WINDOW_HPP
#define WINDOW_HPP

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Drawable.hpp"
#include "Camera.hpp"
#include "Logger.hpp"

class Window
{
    public:
        Window(const char * title, unsigned int width, unsigned int height);
        ~Window();

        void beginDraw();
        void endDraw();
        void update();

        bool isDone();
        void close();

        void draw(Drawable * drawable);

        GLfloat getElapsedTime();

    private:
        static void keyCallback(GLFWwindow * window, int key, int scanCode, int action, int mode);

        /****************************************
         * Data members
        ****************************************/
        GLFWwindow * m_window;
        
        GLfloat      m_deltaTime;
        GLfloat      m_lastFrameTime;
        GLuint       m_width;
        GLuint       m_height;

        Camera *     m_camera;
};

#endif
