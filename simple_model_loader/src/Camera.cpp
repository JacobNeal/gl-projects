#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch)
    : m_position(position), m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
    m_worldUp(up), m_movementSpeed(SPEED), m_mouseSensitivity(SENSITIVITY),
    m_yaw(yaw), m_pitch(pitch)
{
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::processKeyboard(CameraMovement moveDir, GLfloat deltaTime)
{
    GLfloat velocity = m_movementSpeed * deltaTime;

    switch (moveDir)
    {
        case CameraMovement::FORWARD:
            m_position += m_front * velocity;
            break;

        case CameraMovement::BACKWARD:
            m_position -= m_front * velocity;
            break;

        case CameraMovement::LEFT:
            m_position -= m_right * velocity;
            break;

        case CameraMovement::RIGHT:
            m_position += m_right * velocity;
            break;

        default:
            break;
    }
}

void Camera::processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch)
{
    xOffset *= m_mouseSensitivity;
    yOffset *= m_mouseSensitivity;

    m_yaw = glm::mod(m_yaw + xOffset, 360.0f);
    m_pitch += yOffset;

    if (constrainPitch)
    {
        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        else if (m_pitch < -89.0f)
            m_pitch = -89.0f;
    }

    // Update the camera vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;

    GLfloat yawRad = glm::radians(m_yaw);
    GLfloat pitchRad = glm::radians(m_pitch);

    front.x = cos(yawRad) * cos(pitchRad);
    front.y = sin(pitchRad);
    front.z = sin(yawRad) * cos(pitchRad);

    m_front = glm::normalize(front);
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up    = glm::normalize(glm::cross(m_right, m_front));
}
