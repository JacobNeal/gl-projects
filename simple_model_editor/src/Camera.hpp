#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

#define YAW -90.0f
#define PITCH 0.0f
#define SPEED 3.0f
#define SENSITIVITY 0.25f
#define ZOOM 45.0f

enum class CameraMovement
{
    FORWARD, BACKWARD, LEFT, RIGHT
};

class Camera
{
    public:
        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
               GLfloat yaw = YAW, GLfloat pitch = PITCH);

        glm::mat4 getViewMatrix();

        void processKeyboard(CameraMovement moveDir, GLfloat deltaTime);
        void processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true);

        glm::vec3 getPosition();
        glm::vec3 getFrontVector();

    private:
        void updateCameraVectors();

        /****************************************
         * Data members
        ****************************************/
        glm::vec3 m_position;
        glm::vec3 m_front;
        glm::vec3 m_up;
        glm::vec3 m_right;
        glm::vec3 m_worldUp;

        GLfloat   m_movementSpeed;
        GLfloat   m_mouseSensitivity;

        GLfloat   m_yaw;
        GLfloat   m_pitch;
};

#endif
