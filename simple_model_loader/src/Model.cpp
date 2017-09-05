#include "Model.hpp"

Model::Model(std::vector<GLfloat> * vertexData, std::vector<GLuint> * indices)
    : m_vertexCount(vertexData->size()), m_position(0.0, 0.0, 0.0)
{
    // Generate the VBO / VAO
    glGenBuffers(1, &m_VBO);
    glGenVertexArrays(1, &m_VAO);

    // Bind the vertex array object
    glBindVertexArray(m_VAO);

    // Bind the vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexData->size(), &((*vertexData)[0]), GL_STATIC_DRAW);

    LOG("(*vertexData)[0] = " + std::to_string((*vertexData)[0]));
    LOG("Vertex count = " + std::to_string(m_vertexCount));
    LOG("Vertex Stride = " + std::to_string(V_STRIDE));

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
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(aPos, 1.0f);\n"
        "}\0";

    const char * fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
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

void Model::draw()
{
    // Use the shader program
    m_shader.use();

    // Bind the vertex array object
    glBindVertexArray(m_VAO);

    glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);

    // Unbind the vertex array object
    glBindVertexArray(0);
}
