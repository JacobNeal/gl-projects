#include "Model.hpp"

Model::Model(std::vector<GLfloat> * vertexData, std::vector<GLuint> * indices)
    : m_vertexCount(vertexData->size()), m_indexCount(indices->size()), m_position(0.0, 0.0, 0.0)
{
    // Generate the VBO / VAO
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);
    glGenVertexArrays(1, &m_VAO);

    // Bind the vertex array object
    glBindVertexArray(m_VAO);

    // Bind the vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexData->size() * sizeof(GLfloat), &((*vertexData)[0]), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(GLuint), &((*indices)[0]), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, V_STRIDE * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, V_STRIDE * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Normal attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, V_STRIDE * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    // Unbind the vertex array object
    glBindVertexArray(0);

    /************************************************
     * Define the vertex and fragment shader sources
    ************************************************/
    const char * vertexShaderSource =
        "#version 330 core\n"
        "layout (location=0) in vec3 aPos;\n"
        "layout (location=1) in vec3 aColor;\n"
        "layout (location=2) in vec3 aNorm;\n"
        "out vec3 fColor;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = projection * view * model * vec4(aPos, 1.0f);\n"
        "    fColor = aColor;\n"
        "}\0";

    const char * fragmentShaderSource =
        "#version 330 core\n"
        "in vec3 fColor;\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(fColor, 1.0f);\n"
        "}\0";

    m_shader.load(vertexShaderSource, fragmentShaderSource);
}

Model::~Model()
{
    // Deallocate all resources
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
}

GLuint Model::getVertexCount()
{
    return m_vertexCount;
}

GLuint Model::getIndexCount()
{
    return m_indexCount;
}

void Model::draw()
{
    // Use the shader program
    m_shader.use();

    // Bind the vertex array object
    glBindVertexArray(m_VAO);

    //glDrawArrays(GL_TRIANGLES, 0, m_vertexCount / V_STRIDE);
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);

    // Unbind the vertex array object
    glBindVertexArray(0);
}

GLuint Model::getShaderProgram()
{
    return m_shader.program;
}

glm::vec3 Model::getPosition()
{
    return m_position;
}

void Model::setPosition(const glm::vec3 & position)
{
    m_position = position;
}

void Model::move(const GLfloat & x, const GLfloat & y, const GLfloat & z)
{
    m_position.x += x;
    m_position.y += y;
    m_position.z += z;
}

void Model::setColor(const glm::vec3 & color)
{
    m_color = color;
}

glm::vec3 Model::getColor()
{
    return m_color;
}
