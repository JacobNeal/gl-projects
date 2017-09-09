#ifndef MODEL_HPP
#define MODEL_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "Drawable.hpp"
#include "Shader.hpp"
#include "Logger.hpp"

// The vertex stride is 9, because of 9 GLfloats per vertex (x,y,z,r,g,b,nx,ny,nz)
#define V_STRIDE 9

class Model : public Drawable
{
    public:
        Model(std::vector<GLfloat> * vertexData, std::vector<GLuint> * indices);
        virtual ~Model();

        GLuint getVertexCount();
        GLuint getIndexCount();

        // Override virtual methods from Drawable class
        void draw();
        virtual GLuint getShaderProgram();
        virtual glm::vec3 getPosition();
        virtual void setPosition(const glm::vec3 & position);
        virtual void move(const GLfloat & x, const GLfloat & y, const GLfloat & z);
        virtual void setColor(const glm::vec3 & color);
        virtual glm::vec3 getColor();

    private:
        /****************************************
         * Data members
        ****************************************/
        GLuint    m_VBO;
        GLuint    m_VAO;
        GLuint    m_EBO;
        GLuint    m_vertexCount;
        GLuint    m_indexCount;

        glm::vec3 m_position;
        glm::vec3 m_color;
        
        Shader    m_shader;
};

#endif
