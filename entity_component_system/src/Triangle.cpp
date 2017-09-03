#include "Triangle.hpp"

Triangle::Triangle(glm::vec3 position, GLfloat size)
    : m_position(position), m_scale(size)
{
    /****************************************************
     * Define the vertex data and set up the VBO and VAO 
    *****************************************************/
    GLfloat vertices[] = {
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // Top Middle
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Bottom Left
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // Bottom Right
    };

    // Generate the VBO / VAO
    glGenBuffers(1, &m_VBO);
    glGenVertexArrays(1, &m_VAO);

    // Bind the vertex array object
    glBindVertexArray(m_VAO);

    // Bind the vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Unbind the vertex array object
    glBindVertexArray(0);

    /************************************************
     * Define the vertex and fragment shader sources
    ************************************************/
    const char * vertexShaderSource = 
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos, 1.0f);\n"
        "}\0";

     const char * fragmentShaderSource = 
         "#version 330 core\n"
         "out vec4 FragColor;\n"
         "void main()\n"
         "{\n"
         "  FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
         "}\0";

     m_shader.load(vertexShaderSource, fragmentShaderSource);
}

Triangle::~Triangle()
{
    // Deallocate all resources
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
}

void Triangle::setSize(const GLfloat & size)
{
    m_scale = size;
}

void Triangle::draw()
{
    // Use the shader program
    m_shader.use();

    // Bind the vertex array object
    glBindVertexArray(m_VAO);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Unbind the vertex array object
    glBindVertexArray(0);
}
