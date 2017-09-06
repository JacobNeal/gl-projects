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
        ~Model();

        GLuint getVertexCount();
        GLuint getIndexCount();

        virtual void draw();

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
        
        Shader    m_shader;
};

#endif
